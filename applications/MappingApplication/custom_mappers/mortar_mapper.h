//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Philipp Bucher, Jordi Cotela
//
// See Master-Thesis P.Bucher
// "Development and Implementation of a Parallel
//  Framework for Non-Matching Grid Mapping"

#if !defined(KRATOS_MORTAR_MAPPER_H_INCLUDED )
#define  KRATOS_MORTAR_MAPPER_H_INCLUDED

// System includes

// External includes

// Project includes
#include "mapper_matrix_based.h"


namespace Kratos
{

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{
/// Short class definition.

class MortarMapper : public MapperMatrixBased
{
public:

    ///@name Type Definitions
    ///@{

    ///@}
    ///@name Pointer Definitions
    /// Pointer definition of MortarMapper
    KRATOS_CLASS_POINTER_DEFINITION(MortarMapper);

    ///@}
    ///@name Life Cycle
    ///@{

    MortarMapper(ModelPart& i_model_part_origin, ModelPart& i_model_part_destination,
                          Parameters& rJsonParameters) : MapperMatrixBased(
                                  i_model_part_origin, i_model_part_destination, rJsonParameters)
    {
        mpMapperCommunicator->InitializeOrigin(MapperUtilities::Condition_Gauss_Point);
        mpMapperCommunicator->InitializeDestination(MapperUtilities::Condition_Gauss_Point);
        mpMapperCommunicator->Initialize();
        // these three steps correspond to "MapperCommunicator::BuildInterface()"

        mpMapperCommunicator->GetBuilderAndMultiplier()->BuildLHS(scheme, modelpart, Mdo); // could be moved to baseclass...?

        mpMapperCommunicator->GetBuilderAndSolver()->BuildLHS(scheme, modelpart, Mdd); // this would also initialize this "BuilderAndSolver"
    }

    /// Destructor.
    virtual ~MortarMapper() { }

    ///@}
    ///@name Operators
    ///@{

    ///@}
    ///@name Operations
    ///@{

    void UpdateInterface(Kratos::Flags MappingOptions, double SearchRadius) override
    {

    }

    /* This function maps from Origin to Destination */
    void Map(const Variable<double>& rOriginVariable,
             const Variable<double>& rDestinationVariable,
             Kratos::Flags MappingOptions) override
    {   
        InterpolateToDestinationMesh(q_tmp)
        
        mpMapperCommunicator->GetBuilderAndSolver()->BuildRHSAndSolve(scheme, modelpart, Mdd, q_d, q_tmp);

        SetNodalValues();
    }

    /* This function maps from Origin to Destination */
    void Map(const Variable< array_1d<double, 3> >& rOriginVariable,
             const Variable< array_1d<double, 3> >& rDestinationVariable,
             Kratos::Flags MappingOptions) override
    {
        
    }

    /* This function maps from Destination to Origin */
    void InverseMap(const Variable<double>& rOriginVariable,
                    const Variable<double>& rDestinationVariable,
                    Kratos::Flags MappingOptions) override
    {

    }

    /* This function maps from Destination to Origin */
    void InverseMap(const Variable< array_1d<double, 3> >& rOriginVariable,
                    const Variable< array_1d<double, 3> >& rDestinationVariable,
                    Kratos::Flags MappingOptions) override
    {
        
    }

    ///@}
    ///@name Access
    ///@{

    ///@}
    ///@name Inquiry
    ///@{

    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    virtual std::string Info() const override
    {
        return "MortarMapper";
    }

    /// Print information about this object.
    virtual void PrintInfo(std::ostream& rOStream) const override
    {
        rOStream << "MortarMapper";
    }

    /// Print object's data.
    virtual void PrintData(std::ostream& rOStream) const override
    {
    }

    ///@}
    ///@name Friends
    ///@{

    ///@}

protected:

    ///@name Protected static Member Variables
    ///@{

    ///@}
    ///@name Protected member Variables
    ///@{

    ///@}
    ///@name Protected Operators
    ///@{

    ///@}
    ///@name Protected Operations
    ///@{

    ///@}
    ///@name Protected  Access
    ///@{

    ///@}
    ///@name Protected Inquiry
    ///@{

    ///@}
    ///@name Protected LifeCycle
    ///@{

    ///@}

private:

    ///@name Static Member Variables
    ///@{

    ///@}
    ///@name Member Variables
    ///@{

    TSystemMatrixType M_dd;
    TSystemVectorType q_tmp;

    ///@}
    ///@name Private Operators
    ///@{

    ///@}
    ///@name Private Operations
    ///@{

    ///@}
    ///@name Private  Access
    ///@{

    ///@}
    ///@name Private Inquiry
    ///@{

    ///@}
    ///@name Un accessible methods
    ///@{

    /// Assignment operator.
    MortarMapper& operator=(MortarMapper const& rOther);

    /// Copy constructor.
    //MortarMapper(MortarMapper const& rOther);

    ///@}

}; // Class MortarMapper

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{


/// input stream function


inline std::istream & operator >>(std::istream& rIStream,
                                  MortarMapper& rThis)
{
    return rIStream;
}

/// output stream function

inline std::ostream & operator <<(std::ostream& rOStream,
                                  const MortarMapper& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}
///@}

///@} addtogroup block
}  // namespace Kratos.

#endif // KRATOS_MORTAR_MAPPER_H_INCLUDED  defined