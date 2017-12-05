// KRATOS  ___|  |                   |                   |
//       \___ \  __|  __| |   |  __| __| |   |  __| _` | |
//             | |   |    |   | (    |   |   | |   (   | |
//       _____/ \__|_|   \__,_|\___|\__|\__,_|_|  \__,_|_| MECHANICS
//
//  License:		 BSD License
//					 license:
// structural_mechanics_application/license.txt
//
//  Main authors:    Riccardo Rossi
//

#if !defined(KRATOS_STRUCTURAL_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED)
#define KRATOS_STRUCTURAL_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED

// System includes
// #include <map>
// #include <string>

// External includes

// Project includes
#include "includes/define.h"
// #include "includes/kratos_application.h"
// #include "includes/model_part.h"
//#include "structural_mechanics_application.h"
#include "custom_utilities/multipoint_constraint_data.hpp"
#include "custom_utilities/shell_cross_section.hpp"
#include "includes/mat_variables.h"

namespace Kratos
{
typedef array_1d<double, 3> Vector3;
typedef MpcData::Pointer MpcDataPointerType;
typedef boost::shared_ptr<std::vector<MpcDataPointerType>>
    MpcDataSharedPointerVectorType;
typedef std::vector<MpcDataPointerType>
    *MpcDataPointerVectorType;


    // Generalized eigenvalue problem
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, int, BUILD_LEVEL )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Vector, EIGENVALUE_VECTOR)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix , EIGENVECTOR_MATRIX )

    // Geometrical
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, AREA )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, IT )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, IY )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, IZ )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, CROSS_AREA )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, MEAN_RADIUS )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, int,    SECTION_SIDES )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix , GEOMETRIC_STIFFNESS )
    KRATOS_DEFINE_APPLICATION_VARIABLE(STRUCTURAL_MECHANICS_APPLICATION,Vector, LOCAL_AXIS_VECTOR_1)
    KRATOS_DEFINE_APPLICATION_VARIABLE(STRUCTURAL_MECHANICS_APPLICATION,Matrix, LOCAL_ELEMENT_ORIENTATION)
    KRATOS_DEFINE_APPLICATION_VARIABLE(STRUCTURAL_MECHANICS_APPLICATION,double, ORTHOTROPIC_ORIENTATION_ASSIGNMENT)
    KRATOS_DEFINE_APPLICATION_VARIABLE(STRUCTURAL_MECHANICS_APPLICATION,Vector, ORTHOTROPIC_FIBER_ORIENTATION_1)

    // Truss generalized variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, TRUSS_PRESTRESS_PK2)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,bool, TRUSS_IS_CABLE)


    // Beam generalized variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, AREA_EFFECTIVE_Y)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, AREA_EFFECTIVE_Z)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, INERTIA_ROT_Y)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, INERTIA_ROT_Z)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,Vector, LOCAL_AXES_VECTOR)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,bool, LUMPED_MASS_MATRIX)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, TORSIONAL_INERTIA)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, I22)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, I33)

    // Shell generalized variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_STRAIN )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_STRAIN_GLOBAL )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_CURVATURE )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_CURVATURE_GLOBAL )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_FORCE )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_FORCE_GLOBAL )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_MOMENT )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_MOMENT_GLOBAL )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_STRESS_TOP_SURFACE)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_STRESS_TOP_SURFACE_GLOBAL)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_STRESS_MIDDLE_SURFACE)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_STRESS_MIDDLE_SURFACE_GLOBAL)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_STRESS_BOTTOM_SURFACE)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_STRESS_BOTTOM_SURFACE_GLOBAL)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, VON_MISES_STRESS_TOP_SURFACE)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, VON_MISES_STRESS_MIDDLE_SURFACE)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, VON_MISES_STRESS_BOTTOM_SURFACE)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_ORTHOTROPIC_STRESS_BOTTOM_SURFACE)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_ORTHOTROPIC_STRESS_TOP_SURFACE)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_ORTHOTROPIC_STRESS_BOTTOM_SURFACE_GLOBAL)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_ORTHOTROPIC_STRESS_TOP_SURFACE_GLOBAL)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_ORTHOTROPIC_4PLY_THROUGH_THICKNESS)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, TSAI_WU_RESERVE_FACTOR)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_ORTHOTROPIC_LAMINA_STRENGTHS)

    // Membrane generalized variables
    KRATOS_DEFINE_APPLICATION_VARIABLE(STRUCTURAL_MECHANICS_APPLICATION, Vector, MEMBRANE_PRESTRESS)
    // Shell energies
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, SHELL_ELEMENT_MEMBRANE_ENERGY)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, SHELL_ELEMENT_BENDING_ENERGY)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, SHELL_ELEMENT_SHEAR_ENERGY)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, SHELL_ELEMENT_MEMBRANE_ENERGY_FRACTION)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, SHELL_ELEMENT_BENDING_ENERGY_FRACTION)
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, SHELL_ELEMENT_SHEAR_ENERGY_FRACTION)

    // Cross section
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, ShellCrossSection::Pointer, SHELL_CROSS_SECTION )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, int,          SHELL_CROSS_SECTION_OUTPUT_PLY_ID )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double,	SHELL_CROSS_SECTION_OUTPUT_PLY_LOCATION )
    KRATOS_DEFINE_APPLICATION_VARIABLE(STRUCTURAL_MECHANICS_APPLICATION, Matrix, SHELL_ORTHOTROPIC_LAYERS)

    // Nodal stiffness for the nodal concentrated element
    KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS(STRUCTURAL_MECHANICS_APPLICATION, NODAL_STIFFNESS )
    KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS(STRUCTURAL_MECHANICS_APPLICATION, NODAL_DAMPING_RATIO)

    // CONDITIONS
    /* Beam conditions */
    KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS(STRUCTURAL_MECHANICS_APPLICATION, POINT_MOMENT )

    // Adding the SPRISM EAS variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, ALPHA_EAS);
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,bool, EAS_IMP);
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,bool, SPRISM_TL_UL);

    // Adding the SPRISM additional variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,double, ANG_ROT); // TODO: Transform into a vector

    // Adding the Sprism number of transversal integration points
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,int, NINT_TRANS);

    // Adding the SPRISM variable to deactivate the quadratic interpolation
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION,bool, QUAD_ON);

    // Additional strain measures
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Vector, HENCKY_STRAIN_VECTOR);
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, HENCKY_STRAIN_TENSOR);

    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, VON_MISES_STRESS )  

    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Matrix, REFERENCE_DEFORMATION_GRADIENT);
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, REFERENCE_DEFORMATION_GRADIENT_DETERMINANT);
    
    // Rayleigh variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, RAYLEIGH_ALPHA )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, RAYLEIGH_BETA )

    // System damping
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, double, SYSTEM_DAMPING_RATIO )

    // Nodal load variables
    KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( STRUCTURAL_MECHANICS_APPLICATION, POINT_LOAD )
    KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( STRUCTURAL_MECHANICS_APPLICATION, LINE_LOAD )
    KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( STRUCTURAL_MECHANICS_APPLICATION, SURFACE_LOAD )

    // Condition load variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Vector, POINT_LOADS_VECTOR )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Vector, LINE_LOADS_VECTOR )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Vector, SURFACE_LOADS_VECTOR )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Vector, POSITIVE_FACE_PRESSURES_VECTOR )
    KRATOS_DEFINE_APPLICATION_VARIABLE( STRUCTURAL_MECHANICS_APPLICATION, Vector, NEGATIVE_FACE_PRESSURES_VECTOR )

    // For MPC implementations
    KRATOS_DEFINE_VARIABLE(MpcDataSharedPointerVectorType, MPC_DATA_CONTAINER)
}

#endif /* KRATOS_STRUCTURAL_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED */
