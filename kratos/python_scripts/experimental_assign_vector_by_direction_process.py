import math
import KratosMultiphysics

def Factory(settings, Model):
    if(type(settings) != KratosMultiphysics.Parameters):
        raise Exception("expected input shall be a Parameters object, encapsulating a json string")
    return AssignVectorByDirectionProcess(Model, settings["Parameters"])


##all the processes python processes should be derived from "python_process"
class AssignVectorByDirectionProcess(KratosMultiphysics.Process):
    def __init__(self, Model, settings ):
        KratosMultiphysics.Process.__init__(self)

        default_settings = KratosMultiphysics.Parameters("""
            {
                "mesh_id"              : 0,
                "model_part_name"      : "please_specify_model_part_name",
                "variable_name"        : "SPECIFY_VARIABLE_NAME",
                "interval"             : [0.0, 1e30],
                "modulus"              : 1.0,
                "constrained"          : true,
                "direction"            : [1.0, 0.0, 0.0],
                "local_axes"           : {}
            }
            """)

        # Trick: allow "modulus" and "direction" to be a double or a string value (otherwise the ValidateAndAssignDefaults might fail)
        if(settings.Has("modulus")):
            if(settings["modulus"].IsString()):
                default_settings["modulus"].SetString("0.0")

        if(settings.Has("direction")):
            if(settings["direction"].IsString()):
                default_settings["direction"].SetString("Automatic")

        # Detect "End" as a tag and replace it by a large number
        if(settings.Has("interval")):
            if(settings["interval"][1].IsString()):
                if(settings["interval"][1].GetString() == "End"):
                    settings["interval"][1].SetDouble(1e30) # = default_settings["interval"][1]
                else:
                    raise Exception("The second value of interval can be \"End\" or a number, interval currently:"+settings["interval"].PrettyPrintJsonString())

        settings.ValidateAndAssignDefaults(default_settings)

        self.model_part = Model[settings["model_part_name"].GetString()]

        # Construct the component by component parameter objects
        x_params = KratosMultiphysics.Parameters("{}")
        y_params = KratosMultiphysics.Parameters("{}")
        z_params = KratosMultiphysics.Parameters("{}")

        # Component X
        x_params.AddValue("model_part_name",settings["model_part_name"])
        x_params.AddValue("mesh_id",settings["mesh_id"])
        x_params.AddValue("constrained",settings["constrained"])
        x_params.AddValue("interval",settings["interval"])
        x_params.AddEmptyValue("variable_name").SetString(settings["variable_name"].GetString() + "_X")
        x_params.AddValue("local_axes",settings["local_axes"])

        # Component Y
        y_params.AddValue("model_part_name",settings["model_part_name"])
        y_params.AddValue("mesh_id",settings["mesh_id"])
        y_params.AddValue("constrained",settings["constrained"])
        y_params.AddValue("interval",settings["interval"])
        y_params.AddEmptyValue("variable_name").SetString(settings["variable_name"].GetString() + "_Y")
        y_params.AddValue("local_axes",settings["local_axes"])

        # Component Z
        z_params.AddValue("model_part_name",settings["model_part_name"])
        z_params.AddValue("mesh_id",settings["mesh_id"])
        z_params.AddValue("constrained",settings["constrained"])
        z_params.AddValue("interval",settings["interval"])
        z_params.AddEmptyValue("variable_name").SetString(settings["variable_name"].GetString() + "_Z")
        z_params.AddValue("local_axes",settings["local_axes"])

        # "Automatic" direction: get the inwards direction
        if(settings["direction"].IsString()):
            if (settings["direction"].GetString() == "Automatic"):
                # Compute the condition normals
                KratosMultiphysics.NormalCalculationUtils().CalculateOnSimplex(self.model_part, self.model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE])

                # Compute the average conditions normal in the submodelpart of interest
                avg_normal = [0.0, 0.0, 0.0]

                for cond in self.model_part.Conditions:
                    normal = cond.GetValue(KratosMultiphysics.NORMAL)
                    for i in range(0,3):
                        # Note the minus sign! One wants the normal pointing towards the domain.
                        # KratosMultiphysics.NormalCalculationUtils().CalculateOnSimplex gives the outwards normal vector.
                        avg_normal[i] -= normal[i]

                # Sum all the partitions conditions number and average conditions normals
                ncond = len(self.model_part.Conditions)
                # self.model_part.GetCommunicator().SumAll(ncond)
                # for i in range(0,3):
                #     self.model_part.GetCommunicator().SumAll(avg_normal[i])

                for i in range(0,3):
                    avg_normal[i] /= ncond

                avg_normal_norm = math.sqrt(pow(avg_normal[0],2) +
                                            pow(avg_normal[1],2) +
                                            pow(avg_normal[2],2))
                if(avg_normal_norm < 1e-6):
                    raise Exception("Direction norm is close to 0 in AssignVectorByDirectionProcess.")

                unit_direction = []
                for i in range(0,3):
                    unit_direction.append(avg_normal[i]/avg_normal_norm)

        # Direction is given as a vector
        elif(settings["direction"].IsArray()):
            # Normalize direction
            direction_norm = math.sqrt(pow(settings["direction"][0].GetDouble(),2) +
                                       pow(settings["direction"][1].GetDouble(),2) +
                                       pow(settings["direction"][2].GetDouble(),2))
            if(direction_norm < 1e-6):
                raise Exception("Direction norm is close to 0 in AssignVectorByDirectionProcess.")

            unit_direction = []
            for i in range(0,3):
                unit_direction.append(settings["direction"][i].GetDouble()/direction_norm)


        # Set the remainding parameters
        if(settings["modulus"].IsDouble()):
            x_params.AddEmptyValue("value").SetDouble(settings["modulus"].GetDouble()*unit_direction[0])
            y_params.AddEmptyValue("value").SetDouble(settings["modulus"].GetDouble()*unit_direction[1])
            z_params.AddEmptyValue("value").SetDouble(settings["modulus"].GetDouble()*unit_direction[2])
        elif(settings["modulus"].IsString()):
            # The concatenated string is: "direction[i])*(f(x,y,z,t)"
            x_params.AddEmptyValue("value").SetString("("+str(unit_direction[0])+")*("+settings["modulus"].GetString()+")")
            y_params.AddEmptyValue("value").SetString("("+str(unit_direction[1])+")*("+settings["modulus"].GetString()+")")
            z_params.AddEmptyValue("value").SetString("("+str(unit_direction[2])+")*("+settings["modulus"].GetString()+")")

        # Construct a AssignValueProcess for each component
        import experimental_assign_value_process

        self.aux_processes = []
        self.aux_processes.append( experimental_assign_value_process.AssignValueProcess(Model, x_params) )
        self.aux_processes.append( experimental_assign_value_process.AssignValueProcess(Model, y_params) )
        self.aux_processes.append( experimental_assign_value_process.AssignValueProcess(Model, z_params) )

        print("Finished construction of AssignVectorByComponentsProcess")

    def ExecuteInitializeSolutionStep(self):
        for process in self.aux_processes:
            process.ExecuteInitializeSolutionStep()

    def ExecuteFinalizeSolutionStep(self):
        for process in self.aux_processes:
            process.ExecuteFinalizeSolutionStep()
