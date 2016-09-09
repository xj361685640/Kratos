﻿from __future__ import print_function, absolute_import, division

import KratosMultiphysics.KratosUnittest as KratosUnittest
from KratosMultiphysics import *
import math

def GetFilePath(fileName):
    return os.path.dirname(os.path.realpath(__file__)) + "/" + fileName


class TestProcesses(KratosUnittest.TestCase):

    def test_apply_custom_function_process(self):
        model_part = ModelPart("Main")
        model_part.AddNodalSolutionStepVariable(DISPLACEMENT)
        model_part.AddNodalSolutionStepVariable(VISCOSITY)
        model_part_io = ModelPartIO(GetFilePath("test_model_part_io"))
        model_part_io.ReadModelPart(model_part)
        
        settings = Parameters(
            """
            {
                "process_list" : [
                    {
                        "python_module"   : "apply_custom_function_process",
                        "kratos_module" : "KratosMultiphysics",
                        "help"                  : "This process imposes the value by reading it from f(x,y,z,t) field",
                        "process_name"          : "ApplyCustomFunctionProcess",
                        "Parameters"            : {
                            "mesh_id"         : 0,
                            "model_part_name" : "Main",
                            "variable_name"   : "VISCOSITY",
                            "interval"        : [0.0, 10.0],
                            "is_fixed"		  : true,
                            "free_outside_of_interval" : true,
                            "f(x,y,z,t)"      : "x+100.0*y*t**2"
                        }
                    },
                    {
                        "python_module"   : "apply_custom_function_process",
                        "kratos_module" : "KratosMultiphysics",
                        "help"                  : "This process imposes the value by reading it from f(x,y,z,t) field",
                        "process_name"          : "ApplyCustomFunctionProcess",
                        "Parameters"            : {
                            "mesh_id"         : 0,
                            "model_part_name" : "Main",
                            "variable_name"   : "DISPLACEMENT_X",
                            "interval"        : [0.0, 5.0],
                            "is_fixed"		  : true,
                            "free_outside_of_interval" : true,
                            "f(x,y,z,t)"      : "sqrt(x**2+y**2)*t"
                        }
                    }
                ]
                }
            """
            )
        
        Model = {"Main":model_part}
        
        import process_factory
        list_of_processes = process_factory.KratosProcessFactory(Model).ConstructListOfProcesses( settings["process_list"] )
        
        ############################################################
        ##time = 3 - both within the active interval
        model_part.CloneTimeStep(3.0)
        
        for process in list_of_processes:
            process.ExecuteInitializeSolutionStep()

        ##verify the result
        t = model_part.ProcessInfo[TIME]
        for node in model_part.Nodes:
            self.assertEqual(node.GetSolutionStepValue(DISPLACEMENT_X), math.sqrt(node.X**2+node.Y**2)*t)
            self.assertEqual(node.GetSolutionStepValue(VISCOSITY), node.X+100.0*node.Y*t**2)
            self.assertTrue(node.IsFixed(VISCOSITY))
            self.assertTrue(node.IsFixed(DISPLACEMENT_X))
                             
        for process in list_of_processes:
            process.ExecuteFinalizeSolutionStep()

        ##verify the result
        t = model_part.ProcessInfo[TIME]
        for node in model_part.Nodes:
            self.assertFalse(node.IsFixed(VISCOSITY))
            self.assertFalse(node.IsFixed(DISPLACEMENT_X))
                             
        ############################################################
        ##time = 3 - DISPLACEMENT_X is not in the active interval
        model_part.CloneTimeStep(6.0)
        
        for process in list_of_processes:
            process.ExecuteInitializeSolutionStep()

        ##verify the result
        t = model_part.ProcessInfo[TIME]
        for node in model_part.Nodes:
            self.assertEqual(node.GetSolutionStepValue(DISPLACEMENT_X), math.sqrt(node.X**2+node.Y**2)*3.0) ##still the old value
            self.assertEqual(node.GetSolutionStepValue(VISCOSITY), node.X+100.0*node.Y*t**2)
            self.assertTrue(node.IsFixed(VISCOSITY)) 
            self.assertFalse(node.IsFixed(DISPLACEMENT_X)) #it is left unfixed at the end of the previous interval
                             
        for process in list_of_processes:
            process.ExecuteFinalizeSolutionStep()

        ##verify the result
        t = model_part.ProcessInfo[TIME]
        for node in model_part.Nodes:
            self.assertFalse(node.IsFixed(VISCOSITY))
            self.assertFalse(node.IsFixed(DISPLACEMENT_X))


if __name__ == '__main__':
    KratosUnittest.main()