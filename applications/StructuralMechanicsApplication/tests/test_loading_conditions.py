from __future__ import print_function, absolute_import, division
import KratosMultiphysics 

import KratosMultiphysics.StructuralMechanicsApplication as StructuralMechanicsApplication
import KratosMultiphysics.KratosUnittest as KratosUnittest
import math


class TestLoadingConditions(KratosUnittest.TestCase):
    def setUp(self):
        pass

    def _test_LineLoadCondition2D2N(self):
        dim = 2
        mp = KratosMultiphysics.ModelPart("solid_part")
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.DISPLACEMENT)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.REACTION)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.POSITIVE_FACE_PRESSURE)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.NEGATIVE_FACE_PRESSURE)
        
        #create nodes
        mp.CreateNewNode(1,0.0,0.0,0.0)
        mp.CreateNewNode(2,math.sqrt(2),math.sqrt(2.0),0.0)
        lenght = 2.0
        
        #ensure that the property 1 is created
        mp.GetProperties()[1]

        for node in mp.Nodes:
            node.AddDof(KratosMultiphysics.DISPLACEMENT_X, KratosMultiphysics.REACTION_X)
            node.AddDof(KratosMultiphysics.DISPLACEMENT_Y, KratosMultiphysics.REACTION_Y)
            node.AddDof(KratosMultiphysics.DISPLACEMENT_Z, KratosMultiphysics.REACTION_Z)
            
        cond = mp.CreateNewCondition("LineLoadCondition2D2N", 1, [1,2], mp.GetProperties()[1])
        
        lhs = KratosMultiphysics.Matrix(0,0)
        rhs = KratosMultiphysics.Vector(0)
        
        #first we apply a constant LINE_LOAD to theh condition 
        load_on_cond = KratosMultiphysics.Vector(3)
        load_on_cond[0] = 1.0
        load_on_cond[1] = 2.0
        load_on_cond[2] = 0.0 #note that this is a 2D condition
        cond.SetValue(StructuralMechanicsApplication.LINE_LOAD,load_on_cond)
        cond.CalculateLocalSystem(lhs,rhs,mp.ProcessInfo)
        self.assertEqual(rhs[0],0.5*lenght)
        self.assertEqual(rhs[1],1.0*lenght)
        self.assertEqual(rhs[2],0.5*lenght)
        self.assertEqual(rhs[3],1.0*lenght)
        
        ##now the condition is something like
        ##    2 
        ##  +/
        ##  /- 
        ## 1
        #with the + and - sides as indicated. (positive face is the one from which the normal to the face goes out)
        ##applying a NEGATIVE_FACE_PRESSURE implies applying a pressure on the - face, which hence goes in the direction of the normal (-1,1)
        ##applying a POSITIVE_FACE_PRESSURE implies applying a distributed force to the + face, which corresponds to a force going in the direciton of (1,-1), that is, the opposite to the normal
        ##here 
        ##we add to it a NEGATIVE_FACE_PRESSURE of 10 corresponding to a a distributed force (10*cos(45),-10*sin(45)) 
        ##togheter with a POSITIVE_FACE_PRESSURE of 5 corresponding to a LINE_LOAD (-5*cos(45),5*cos(45))
        ##together with the previousy applied LINE_LOAD this gives an equivalent load of (1+5*cos(45),2.0-5*sin(45))
        cond.SetValue(KratosMultiphysics.POSITIVE_FACE_PRESSURE,10.0)
        cond.SetValue(KratosMultiphysics.NEGATIVE_FACE_PRESSURE,5.0)
        cond.CalculateLocalSystem(lhs,rhs,mp.ProcessInfo)
        self.assertAlmostEqual(rhs[0],0.5*(1+5*math.sqrt(2.0)/2.0)*lenght)
        self.assertAlmostEqual(rhs[1],0.5*(2.0-5*math.sqrt(2.0)/2.0)*lenght)
        self.assertAlmostEqual(rhs[2],0.5*(1+5*math.sqrt(2.0)/2.0)*lenght)
        self.assertAlmostEqual(rhs[3], 0.5*(2.0-5*math.sqrt(2.0)/2.0)*lenght)
        

        ##finally we apply TO THE NODES, a linearly varying POSITIVE_FACE_PRESSURE ranging from -100.0 to -200.0
        mp.Nodes[1].SetSolutionStepValue(KratosMultiphysics.POSITIVE_FACE_PRESSURE,0,-100.0)
        mp.Nodes[2].SetSolutionStepValue(KratosMultiphysics.POSITIVE_FACE_PRESSURE,0,-200.0)
        cond.CalculateLocalSystem(lhs,rhs,mp.ProcessInfo)
        reference_res = [-89.7453702522736,92.7453702522736,-113.31559629182519,116.3155962918252]
        self.assertAlmostEqual(rhs[0],reference_res[0])
        self.assertAlmostEqual(rhs[1],reference_res[1])
        self.assertAlmostEqual(rhs[2],reference_res[2])
        self.assertAlmostEqual(rhs[3],reference_res[3])
        
    def _test_LineLoadCondition2D2NAngle(self):
        dim = 2
        mp = KratosMultiphysics.ModelPart("solid_part")
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.DISPLACEMENT)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.REACTION)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.POSITIVE_FACE_PRESSURE)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.NEGATIVE_FACE_PRESSURE)
        
        #create nodes
        mp.CreateNewNode(1,0.0,0.0,0.0)
        mp.CreateNewNode(2,1.0,0.0,0.0)
        mp.CreateNewNode(3,1.0,1.0,0.0)
        lenght = 1.0
        
        #ensure that the property 1 is created
        mp.GetProperties()[1]

        for node in mp.Nodes:
            node.AddDof(KratosMultiphysics.DISPLACEMENT_X, KratosMultiphysics.REACTION_X)
            node.AddDof(KratosMultiphysics.DISPLACEMENT_Y, KratosMultiphysics.REACTION_Y)
            node.AddDof(KratosMultiphysics.DISPLACEMENT_Z, KratosMultiphysics.REACTION_Z)
            
        cond1 = mp.CreateNewCondition("LineLoadCondition2D2N", 1, [1,2], mp.GetProperties()[1])
        cond2 = mp.CreateNewCondition("LineLoadCondition2D2N", 2, [2,3], mp.GetProperties()[1])
        
        rhs = KratosMultiphysics.Vector(6)
        rhs[0] = 0.0
        rhs[1] = 0.0
        rhs[2] = 0.0
        rhs[3] = 0.0
        rhs[4] = 0.0
        rhs[5] = 0.0
        
        #first we apply a constant LINE_LOAD to theh condition 
        load_on_cond = KratosMultiphysics.Vector(3)
        load_on_cond[0] = 1.0
        load_on_cond[1] = 0.0
        load_on_cond[2] = 0.0 #note that this is a 2D condition
        cond1.SetValue(StructuralMechanicsApplication.LINE_LOAD,load_on_cond)
        load_on_cond[0] =  0.0
        load_on_cond[1] = -1.0
        cond2.SetValue(StructuralMechanicsApplication.LINE_LOAD,load_on_cond)
        
        linear_solver = KratosMultiphysics.SkylineLUFactorizationSolver()
        builder_and_solver = KratosMultiphysics.ResidualBasedBlockBuilderAndSolver(linear_solver)
        scheme = KratosMultiphysics.ResidualBasedIncrementalUpdateStaticScheme()
        
        builder_and_solver.SetEchoLevel(0)
        
        builder_and_solver.Check(mp)
        builder_and_solver.SetUpDofSet(scheme, mp);
        builder_and_solver.SetUpSystem(mp);
        builder_and_solver.BuildRHS(scheme, mp, rhs)
        
        self.assertEqual(rhs[0], 0.5*lenght)
        self.assertEqual(rhs[1], 0.0*lenght)
        self.assertEqual(rhs[2], 0.5*lenght)
        self.assertEqual(rhs[3],-0.5*lenght)
        self.assertEqual(rhs[4], 0.0*lenght)
        self.assertEqual(rhs[5],-0.5*lenght)

    def _test_SurfaceLoadCondition3D4N(self):
        dim = 2
        mp = KratosMultiphysics.ModelPart("solid_part")
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.DISPLACEMENT)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.REACTION)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.POSITIVE_FACE_PRESSURE)
        mp.AddNodalSolutionStepVariable(KratosMultiphysics.NEGATIVE_FACE_PRESSURE)
        
        #create nodes
        mp.CreateNewNode(1,0.0,0.0,0.0)
        mp.CreateNewNode(2,0.0,0.0,1.0)
        mp.CreateNewNode(3,math.sqrt(2),math.sqrt(2.0),0.0)
        mp.CreateNewNode(4,math.sqrt(2),math.sqrt(2.0),1.0)
        lenght = 2.0
        width = 1.0
        
        #ensure that the property 1 is created
        mp.GetProperties()[1]

        for node in mp.Nodes:
            node.AddDof(KratosMultiphysics.DISPLACEMENT_X, KratosMultiphysics.REACTION_X)
            node.AddDof(KratosMultiphysics.DISPLACEMENT_Y, KratosMultiphysics.REACTION_Y)
            node.AddDof(KratosMultiphysics.DISPLACEMENT_Z, KratosMultiphysics.REACTION_Z)
            

        cond = mp.CreateNewCondition("SurfaceLoadCondition3D4N", 1, [1,2,4,3], mp.GetProperties()[1])
        
        #cond.Check()
        
        lhs = KratosMultiphysics.Matrix(0,0)
        rhs = KratosMultiphysics.Vector(0)
        
        #first we apply a constant SURFACE_LOAD to theh condition 
        load_on_cond = KratosMultiphysics.Vector(3)
        load_on_cond[0] = 1.0
        load_on_cond[1] = 2.0
        load_on_cond[2] = 0.0 #note that this is a 2D condition
        cond.SetValue(StructuralMechanicsApplication.SURFACE_LOAD,load_on_cond)
        cond.CalculateLocalSystem(lhs,rhs,mp.ProcessInfo)
        self.assertAlmostEqual(rhs[0],0.25*lenght); self.assertAlmostEqual(rhs[1],0.5*1.0*lenght); self.assertAlmostEqual(rhs[2],0.0)
        self.assertAlmostEqual(rhs[3],0.25*lenght); self.assertAlmostEqual(rhs[4],0.5*1.0*lenght); self.assertAlmostEqual(rhs[5],0.0)
        self.assertAlmostEqual(rhs[6],0.25*lenght); self.assertAlmostEqual(rhs[7],0.5*1.0*lenght); self.assertAlmostEqual(rhs[8],0.0)
        self.assertAlmostEqual(rhs[9],0.25*lenght); self.assertAlmostEqual(rhs[10],0.5*1.0*lenght); self.assertAlmostEqual(rhs[11],0.0)        
        
        ##now the condition is something like
        ##    2 
        ##  +/
        ##  /- 
        ## 1
        #with the + and - sides as indicated. (positive face is the one from which the normal to the face goes out)
        ##applying a NEGATIVE_FACE_PRESSURE implies applying a pressure on the - face, which hence goes in the direction of the normal (-1,1)
        ##applying a POSITIVE_FACE_PRESSURE implies applying a distributed force to the + face, which corresponds to a force going in the direciton of (1,-1), that is, the opposite to the normal
        ##here 
        ##we add to it a NEGATIVE_FACE_PRESSURE of 10 corresponding to a a distributed force (10*cos(45),-10*sin(45))*width
        ##togheter with a POSITIVE_FACE_PRESSURE of 5 corresponding to a LINE_LOAD (-5*cos(45),5*cos(45))*width
        ##together with the previousy applied LINE_LOAD this gives an equivalent load of 0.5*(1+5*cos(45),2.0-5*sin(45))
        cond.SetValue(KratosMultiphysics.POSITIVE_FACE_PRESSURE,10.0)
        cond.SetValue(KratosMultiphysics.NEGATIVE_FACE_PRESSURE,5.0)
        cond.CalculateLocalSystem(lhs,rhs,mp.ProcessInfo)
        fxnodal = (1.0 + 5.0*math.sqrt(2.0)/2.0) * lenght*width / 4.0
        fynodal = (2.0 - 5.0*math.sqrt(2.0)/2.0) * lenght*width / 4.0
        for i in range(4):
            base = i*3
            self.assertAlmostEqual(rhs[base+0],fxnodal)
            self.assertAlmostEqual(rhs[base+1],fynodal)
            self.assertAlmostEqual(rhs[base+2],0.0)
        
        ##finally we apply TO THE NODES, a linearly varying POSITIVE_FACE_PRESSURE ranging from -100.0 to -200.0
        mp.Nodes[1].SetSolutionStepValue(KratosMultiphysics.POSITIVE_FACE_PRESSURE,0,-100.0)
        mp.Nodes[2].SetSolutionStepValue(KratosMultiphysics.POSITIVE_FACE_PRESSURE,0,-100.0)
        mp.Nodes[3].SetSolutionStepValue(KratosMultiphysics.POSITIVE_FACE_PRESSURE,0,-200.0)
        mp.Nodes[4].SetSolutionStepValue(KratosMultiphysics.POSITIVE_FACE_PRESSURE,0,-200.0)
        cond.CalculateLocalSystem(lhs,rhs,mp.ProcessInfo)
        reference_res = [-44.872685126136794,46.372685126136815,0.0,-44.87268512613681,46.3726851261368,0.0,-56.657798145912594,58.1577981459126,0.0,-56.65779814591261,58.157798145912615,0.0]
        for i in range(len(rhs)):
            self.assertAlmostEqual(rhs[i],reference_res[i])     
        
    def test_execution(self):
        self._test_LineLoadCondition2D2N()
        self._test_LineLoadCondition2D2NAngle()
        self._test_SurfaceLoadCondition3D4N()
        
if __name__ == '__main__':
    KratosUnittest.main()