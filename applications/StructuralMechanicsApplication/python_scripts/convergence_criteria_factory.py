## This script collects the available convergence criteria to be used in the SolidMechanicsApplication

from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7
#import kratos core and applications
import KratosMultiphysics
import KratosMultiphysics.StructuralMechanicsApplication as StructuralMechanicsApplication

# Check that KratosMultiphysics was imported in the main script
KratosMultiphysics.CheckForPreviousImport()

# Convergence criteria class
class convergence_criterion:
    def __init__(self, convergence_criterion_parameters):
        # Note that all the convergence settings are introduced via a Kratos parameters object.
        
        D_RT = convergence_criterion_parameters["displacement_relative_tolerance"].GetDouble()
        D_AT = convergence_criterion_parameters["displacement_absolute_tolerance"].GetDouble()
        R_RT = convergence_criterion_parameters["residual_relative_tolerance"].GetDouble()
        R_AT = convergence_criterion_parameters["residual_absolute_tolerance"].GetDouble()
        
        echo_level = convergence_criterion_parameters["echo_level"].GetInt()
        convergence_crit = convergence_criterion_parameters["convergence_criterion"].GetString()
        
        if(echo_level >= 1):
            print("::[Mechanical Solver]:: CONVERGENCE CRITERION : ", convergence_criterion)

        rotation_dofs = False
        if(convergence_criterion_parameters.Has("rotation_dofs")):
            if(convergence_criterion_parameters["rotation_dofs"].GetBool()):
                rotation_dofs = True
        
        # Convergence criteria if there are rotation DOFs in the problem
        if(rotation_dofs == True):
            if(convergence_crit == "displacement_criterion"):
                self.mechanical_convergence_criterion = StructuralMechanicsApplication.DisplacementAndOtherDoFCriteria(D_RT, D_AT)
                #self.mechanical_convergence_criterion.SetEchoLevel(echo_level)
                
            elif(convergence_crit == "residual_criterion"):
                self.mechanical_convergence_criterion = StructuralMechanicsApplication.ResidualDisplacementAndOtherDoFCriteria(R_RT, R_AT)
                #self.mechanical_convergence_criterion.SetEchoLevel(echo_level)
                
            elif(convergence_crit == "and_criterion"):
                Displacement = StructuralMechanicsApplication.DisplacementAndOtherDoFCriteria(D_RT, D_AT)
                Displacement.SetEchoLevel(echo_level)
                Residual = StructuralMechanicsApplication.ResidualDisplacementAndOtherDoFCriteria(R_RT, R_AT)
                Residual.SetEchoLevel(echo_level)
                self.mechanical_convergence_criterion = KratosMultiphysics.AndCriteria(Residual, Displacement)
                
            elif(convergence_crit == "or_criterion"):
                Displacement = StructuralMechanicsApplication.DisplacementAndOtherDoFCriteria(D_RT, D_AT)
                Displacement.SetEchoLevel(echo_level)
                Residual = StructuralMechanicsApplication.ResidualDisplacementAndOtherDoFCriteria(R_RT, R_AT)
                Residual.SetEchoLevel(echo_level)
                self.mechanical_convergence_criterion = KratosMultiphysics.OrCriteria(Residual, Displacement)
            else:
                err_msg =  "The requested convergence criterion \"" + convergence_crit + "\" is not available!\n"
                err_msg += "Available options are: \"displacement_criterion\", \"residual_criterion\", \"and_criterion\", \"or_criterion\""
                raise Exception(err_msg)
            
        # Convergence criteria without rotation DOFs        
        else:
            if(convergence_crit == "displacement_criterion"):
                self.mechanical_convergence_criterion = KratosMultiphysics.DisplacementCriteria(D_RT, D_AT)
                self.mechanical_convergence_criterion.SetEchoLevel(echo_level)
                
            elif(convergence_crit == "residual_criterion"):
                self.mechanical_convergence_criterion = KratosMultiphysics.ResidualCriteria(R_RT, R_AT)
                self.mechanical_convergence_criterion.SetEchoLevel(echo_level)
                    
            elif(convergence_crit == "and_criterion"):
                Displacement = KratosMultiphysics.DisplacementCriteria(D_RT, D_AT)
                Displacement.SetEchoLevel(echo_level)
                Residual = KratosMultiphysics.ResidualCriteria(R_RT, R_AT)
                Residual.SetEchoLevel(echo_level)
                self.mechanical_convergence_criterion = KratosMultiphysics.AndCriteria(Residual, Displacement)
                
            elif(convergence_crit == "or_criterion"):
                Displacement = KratosMultiphysics.DisplacementCriteria(D_RT, D_AT)
                Displacement.SetEchoLevel(echo_level)
                Residual = KratosMultiphysics.ResidualCriteria(R_RT, R_AT)
                Residual.SetEchoLevel(echo_level)
                self.mechanical_convergence_criterion = KratosMultiphysics.OrCriteria(Residual, Displacement)
            else:
                err_msg =  "The requested convergence criterion \"" + convergence_crit + "\" is not available!\n"
                err_msg += "Available options are: \"displacement_criterion\", \"residual_criterion\", \"and_criterion\", \"or_criterion\""
                raise Exception(err_msg)
        

