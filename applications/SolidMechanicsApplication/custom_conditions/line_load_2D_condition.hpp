//
//   Project Name:        KratosSolidMechanicsApplication $
//   Last modified by:    $Author:            JMCarbonell $
//   Date:                $Date:                July 2013 $
//   Revision:            $Revision:                  0.0 $
//
//

#if !defined(KRATOS_LINE_LOAD_2D_CONDITION_H_INCLUDED )
#define  KRATOS_LINE_LOAD_2D_CONDITION_H_INCLUDED



// System includes

// External includes

// Project includes
#include "custom_conditions/line_load_3D_condition.hpp"

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

/// Force Load Condition for 3D and 2D geometries. (base class)

/**
 * Implements a Force Load definition for structural analysis.
 * This works for arbitrary geometries in 3D and 2D (base class)
 */
class LineLoad2DCondition
    : public LineLoad3DCondition
{
public:

    ///@name Type Definitions
    ///@{
    // Counted pointer of LineLoad2DCondition
    KRATOS_CLASS_POINTER_DEFINITION( LineLoad2DCondition );
    ///@}

    ///@name Life Cycle
    ///@{

    /// Default constructor.
    LineLoad2DCondition( IndexType NewId, GeometryType::Pointer pGeometry );

    LineLoad2DCondition( IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties );

    /// Copy constructor
    LineLoad2DCondition( LineLoad2DCondition const& rOther);

    /// Destructor
    virtual ~LineLoad2DCondition();

    ///@}
    ///@name Operators
    ///@{


    ///@}
    ///@name Operations
    ///@{

    /**
     * creates a new condition pointer
     * @param NewId: the ID of the new condition
     * @param ThisNodes: the nodes of the new condition
     * @param pProperties: the properties assigned to the new condition
     * @return a Pointer to the new condition
     */
    Condition::Pointer Create(IndexType NewId,
			      NodesArrayType const& ThisNodes,
			      PropertiesType::Pointer pProperties ) const;


    /**
     * clones the selected condition variables, creating a new one
     * @param NewId: the ID of the new condition
     * @param ThisNodes: the nodes of the new condition
     * @param pProperties: the properties assigned to the new condition
     * @return a Pointer to the new condition
     */
    Condition::Pointer Clone(IndexType NewId, 
			     NodesArrayType const& ThisNodes) const;



    //************* COMPUTING  METHODS


    /**
     * This function provides the place to perform checks on the completeness of the input.
     * It is designed to be called only once (or anyway, not often) typically at the beginning
     * of the calculations, so to verify that nothing is missing from the input
     * or that no common error is found.
     * @param rCurrentProcessInfo
     */
    virtual int Check( const ProcessInfo& rCurrentProcessInfo );

    ///@}
    ///@name Access
    ///@{
    ///@}
    ///@name Inquiry
    ///@{
    ///@}
    ///@name Input and output
    ///@{
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
    LineLoad2DCondition() {};
    ///@}
    ///@name Protected Operators
    ///@{
    ///@}
    ///@name Protected Operations
    ///@{

    /**
     * Initialize System Matrices
     */
    virtual void InitializeGeneralVariables(GeneralVariables& rVariables, 
					    const ProcessInfo& rCurrentProcessInfo);

    /**
     * Calculate Condition Kinematics
     */
    virtual void CalculateKinematics(GeneralVariables& rVariables, 
				     const double& rPointNumber);

    /**
     * Calculation of the Vector Force of the Condition
     */
    virtual Vector& CalculateVectorForce(Vector& rVectorForce, GeneralVariables& rVariables);


    /**
     * Calculation of the Integration Weight
     */
    virtual double& CalculateIntegrationWeight(double& rIntegrationWeight);


    /**
     * Calculation of the Load Stiffness Matrix which usually is subtracted to the global stiffness matrix
     */
    virtual void CalculateAndAddKuug(MatrixType& rLeftHandSideMatrix,
				     GeneralVariables& rVariables,
				     double& rIntegrationWeight);

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
    ///@name Serialization
    ///@{

    friend class Serializer;

    virtual void save( Serializer& rSerializer ) const
    {
        KRATOS_SERIALIZE_SAVE_BASE_CLASS( rSerializer, LineLoad3DCondition )
    }

    virtual void load( Serializer& rSerializer )
    {
        KRATOS_SERIALIZE_LOAD_BASE_CLASS( rSerializer, LineLoad3DCondition )
    }


}; // class LineLoad2DCondition.

} // namespace Kratos.

#endif // KRATOS_LINE_LOAD_2D_CONDITION_H_INCLUDED defined 
