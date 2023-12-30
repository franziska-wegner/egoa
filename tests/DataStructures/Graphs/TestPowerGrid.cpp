/*
 * TestPowerGrid.cpp
 *
 *  Created on: Mar 02, 2019
 *      Author: Franziska Wegner
 */

#include "TestPowerGrid.hpp"

using testing::StrEq;

namespace egoa::test {

// ***********************************************************************
// ***********************************************************************
#pragma mark BaseMva
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , BaseMva )
{
   EXPECT_EQ ( 1,      network_.BaseMva() );
   EXPECT_EQ ( 1, networkConst_.BaseMva() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , BaseMva )
{
   EXPECT_EQ ( 1,      network_.BaseMva() );
   EXPECT_EQ ( 1, networkConst_.BaseMva() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , BaseMva )
{
   EXPECT_EQ ( 1,      network_.BaseMva() );
   EXPECT_EQ ( 1, networkConst_.BaseMva() );
}

TEST_F ( TestPowerGridPyPsaExample
       , BaseMva )
{
   EXPECT_EQ ( 1,      network_.BaseMva() );
   EXPECT_EQ ( 1, networkConst_.BaseMva() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark ThetaBound
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , ThetaBound )
{
   EXPECT_EQ ( -Const::REAL_INFTY,      network_.ThetaBound().Minimum() );
   EXPECT_EQ ( -Const::REAL_INFTY, networkConst_.ThetaBound().Minimum() );

   EXPECT_EQ ( Const::REAL_INFTY,      network_.ThetaBound().Maximum() );
   EXPECT_EQ ( Const::REAL_INFTY, networkConst_.ThetaBound().Maximum() );

   EXPECT_TRUE ( Bound<>(-Const::REAL_INFTY,Const::REAL_INFTY) == networkConst_.ThetaBound() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , ThetaBound )
{
   EXPECT_EQ ( -2.61799, round(      network_.ThetaBound().Minimum() * 100000 ) / 100000 );
   EXPECT_EQ ( -2.61799, round( networkConst_.ThetaBound().Minimum() * 100000 ) / 100000 );

   EXPECT_EQ (  2.61799, round(      network_.ThetaBound().Maximum() * 100000 ) / 100000 );
   EXPECT_EQ (  2.61799, round( networkConst_.ThetaBound().Maximum() * 100000 ) / 100000 );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , ThetaBound )
{
   EXPECT_EQ ( -2.61799, round(      network_.ThetaBound().Minimum() * 100000 ) / 100000 );
   EXPECT_EQ ( -2.61799, round( networkConst_.ThetaBound().Minimum() * 100000 ) / 100000 );

   EXPECT_EQ (  2.61799, round(      network_.ThetaBound().Maximum() * 100000 ) / 100000 );
   EXPECT_EQ (  2.61799, round( networkConst_.ThetaBound().Maximum() * 100000 ) / 100000 );
}

TEST_F ( TestPowerGridPyPsaExample
       , ThetaBound )
{
   EXPECT_EQ ( -Const::REAL_INFTY,      network_.ThetaBound().Minimum() );
   EXPECT_EQ ( -Const::REAL_INFTY, networkConst_.ThetaBound().Minimum() );

   EXPECT_EQ ( Const::REAL_INFTY,      network_.ThetaBound().Maximum() );
   EXPECT_EQ ( Const::REAL_INFTY, networkConst_.ThetaBound().Maximum() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorBoundType
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , GeneratorBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.GeneratorBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , GeneratorBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.GeneratorBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , GeneratorBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.GeneratorBoundType() );
}

TEST_F ( TestPowerGridPyPsaExample
       , GeneratorBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.GeneratorBoundType() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark LoadBoundType
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , LoadBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , LoadBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , LoadBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridPyPsaExample
       , LoadBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.LoadBoundType() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark MakeBounded
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , MakeBounded )
{
    network_.MakeBounded ();
    EXPECT_EQ ( Vertices::BoundType::bounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , MakeBounded )
{
    network_.MakeBounded ();
    EXPECT_EQ ( Vertices::BoundType::bounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , MakeBounded )
{
    network_.MakeBounded ();
    EXPECT_EQ ( Vertices::BoundType::bounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridPyPsaExample
       , MakeBounded )
{
    network_.MakeBounded ();
    EXPECT_EQ ( Vertices::BoundType::bounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.LoadBoundType() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark MakeUnbounded
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , MakeUnbounded )
{
    network_.MakeUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , MakeUnbounded )
{
    network_.MakeUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , MakeUnbounded )
{
    network_.MakeUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridPyPsaExample
       , MakeUnbounded )
{
    network_.MakeUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.LoadBoundType() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark MakePureUnbounded
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , MakePureUnbounded )
{
    network_.MakePureUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , MakePureUnbounded )
{
    network_.MakePureUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , MakePureUnbounded )
{
    network_.MakePureUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridPyPsaExample
       , MakePureUnbounded )
{
    network_.MakePureUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, networkConst_.LoadBoundType() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark MakeExact
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , MakeExact )
{
    network_.MakeExact ();
    EXPECT_EQ ( Vertices::BoundType::exact,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , MakeExact )
{
    network_.MakeExact ();
    EXPECT_EQ ( Vertices::BoundType::exact,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , MakeExact )
{
    network_.MakeExact ();
    EXPECT_EQ ( Vertices::BoundType::exact,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.LoadBoundType() );
}

TEST_F ( TestPowerGridPyPsaExample
       , MakeExact )
{
    network_.MakeExact ();
    EXPECT_EQ ( Vertices::BoundType::exact,      network_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.GeneratorBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact,      network_.LoadBoundType() );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.LoadBoundType() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark IsBounded
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , IsBounded )
{
    EXPECT_FALSE (      network_.IsBounded () );
    EXPECT_FALSE ( networkConst_.IsBounded () );
    network_.MakeBounded ();
    EXPECT_TRUE  (      network_.IsBounded () );
    EXPECT_TRUE  ( networkConst_.IsBounded () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , IsBounded )
{
    EXPECT_FALSE (      network_.IsBounded () );
    EXPECT_FALSE ( networkConst_.IsBounded () );
    network_.MakeBounded ();
    EXPECT_TRUE  (      network_.IsBounded () );
    EXPECT_TRUE  ( networkConst_.IsBounded () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , IsBounded )
{
    EXPECT_FALSE (      network_.IsBounded () );
    EXPECT_FALSE ( networkConst_.IsBounded () );
    network_.MakeBounded ();
    EXPECT_TRUE  (      network_.IsBounded () );
    EXPECT_TRUE  ( networkConst_.IsBounded () );
}

TEST_F ( TestPowerGridPyPsaExample
       , IsBounded )
{
    EXPECT_FALSE (      network_.IsBounded () );
    EXPECT_FALSE ( networkConst_.IsBounded () );
    network_.MakeBounded ();
    EXPECT_TRUE  (      network_.IsBounded () );
    EXPECT_TRUE  ( networkConst_.IsBounded () );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark IsUnbounded
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , IsUnbounded )
{
    EXPECT_FALSE (      network_.IsUnbounded () );
    EXPECT_FALSE ( networkConst_.IsUnbounded () );
    network_.MakeUnbounded ();
    EXPECT_TRUE  (      network_.IsUnbounded () );
    EXPECT_TRUE  ( networkConst_.IsUnbounded () );
    network_.MakeBounded ();
    EXPECT_FALSE (      network_.IsUnbounded () );
    EXPECT_FALSE ( networkConst_.IsUnbounded () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , IsUnbounded )
{
    EXPECT_FALSE (      network_.IsUnbounded () );
    EXPECT_FALSE ( networkConst_.IsUnbounded () );
    network_.MakeUnbounded ();
    EXPECT_TRUE  (      network_.IsUnbounded () );
    EXPECT_TRUE  ( networkConst_.IsUnbounded () );
    network_.MakeBounded ();
    EXPECT_FALSE (      network_.IsUnbounded () );
    EXPECT_FALSE ( networkConst_.IsUnbounded () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , IsUnbounded )
{
    EXPECT_FALSE (      network_.IsUnbounded () );
    EXPECT_FALSE ( networkConst_.IsUnbounded () );
    network_.MakeUnbounded ();
    EXPECT_TRUE  (      network_.IsUnbounded () );
    EXPECT_TRUE  ( networkConst_.IsUnbounded () );
    network_.MakeBounded ();
    EXPECT_FALSE (      network_.IsUnbounded () );
    EXPECT_FALSE ( networkConst_.IsUnbounded () );
}

TEST_F ( TestPowerGridPyPsaExample
       , IsUnbounded )
{
    EXPECT_FALSE (      network_.IsUnbounded () );
    EXPECT_FALSE ( networkConst_.IsUnbounded () );
    network_.MakeUnbounded ();
    EXPECT_TRUE  (      network_.IsUnbounded () );
    EXPECT_TRUE  ( networkConst_.IsUnbounded () );
    network_.MakeBounded ();
    EXPECT_FALSE (      network_.IsUnbounded () );
    EXPECT_FALSE ( networkConst_.IsUnbounded () );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark IsPureUnbounded
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , IsPureUnbounded )
{
    EXPECT_FALSE (      network_.IsPureUnbounded () );
    EXPECT_FALSE ( networkConst_.IsPureUnbounded () );
    network_.MakePureUnbounded ();
    EXPECT_TRUE  (      network_.IsPureUnbounded () );
    EXPECT_TRUE  ( networkConst_.IsPureUnbounded () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , IsPureUnbounded )
{
    EXPECT_FALSE (      network_.IsPureUnbounded () );
    EXPECT_FALSE ( networkConst_.IsPureUnbounded () );
    network_.MakePureUnbounded ();
    EXPECT_TRUE  (      network_.IsPureUnbounded () );
    EXPECT_TRUE  ( networkConst_.IsPureUnbounded () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , IsPureUnbounded )
{
    EXPECT_FALSE (      network_.IsPureUnbounded () );
    EXPECT_FALSE ( networkConst_.IsPureUnbounded () );
    network_.MakePureUnbounded ();
    EXPECT_TRUE  (      network_.IsPureUnbounded () );
    EXPECT_TRUE  ( networkConst_.IsPureUnbounded () );
}

TEST_F ( TestPowerGridPyPsaExample
       , IsPureUnbounded )
{
    EXPECT_FALSE (      network_.IsPureUnbounded () );
    EXPECT_FALSE ( networkConst_.IsPureUnbounded () );
    network_.MakePureUnbounded ();
    EXPECT_TRUE  (      network_.IsPureUnbounded () );
    EXPECT_TRUE  ( networkConst_.IsPureUnbounded () );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark IsExact
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , IsExact )
{
    EXPECT_FALSE (      network_.IsExact () );
    EXPECT_FALSE ( networkConst_.IsExact () );
    network_.MakeExact ();
    EXPECT_TRUE  (      network_.IsExact () );
    EXPECT_TRUE  ( networkConst_.IsExact () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , IsExact )
{
    EXPECT_FALSE (      network_.IsExact () );
    EXPECT_FALSE ( networkConst_.IsExact () );
    network_.MakeExact ();
    EXPECT_TRUE  (      network_.IsExact () );
    EXPECT_TRUE  ( networkConst_.IsExact () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , IsExact )
{
    EXPECT_FALSE (      network_.IsExact () );
    EXPECT_FALSE ( networkConst_.IsExact () );
    network_.MakeExact ();
    EXPECT_TRUE  (      network_.IsExact () );
    EXPECT_TRUE  ( networkConst_.IsExact () );
}

TEST_F ( TestPowerGridPyPsaExample
       , IsExact )
{
    EXPECT_FALSE (      network_.IsExact () );
    EXPECT_FALSE ( networkConst_.IsExact () );
    network_.MakeExact ();
    EXPECT_TRUE  (      network_.IsExact () );
    EXPECT_TRUE  ( networkConst_.IsExact () );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark NetworkBoundType
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , NetworkBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.NetworkBoundType () );
    network_.MakeBounded ();
    EXPECT_EQ ( Vertices::BoundType::bounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.NetworkBoundType () );
    network_.MakeUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.NetworkBoundType () );
    network_.MakePureUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, networkConst_.NetworkBoundType () );
    network_.MakeExact ();
    EXPECT_EQ ( Vertices::BoundType::exact, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.NetworkBoundType () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , NetworkBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.NetworkBoundType () );
    network_.MakeBounded ();
    EXPECT_EQ ( Vertices::BoundType::bounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.NetworkBoundType () );
    network_.MakeUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.NetworkBoundType () );
    network_.MakePureUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, networkConst_.NetworkBoundType () );
    network_.MakeExact ();
    EXPECT_EQ ( Vertices::BoundType::exact, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.NetworkBoundType () );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , NetworkBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.NetworkBoundType () );
    network_.MakeBounded ();
    EXPECT_EQ ( Vertices::BoundType::bounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.NetworkBoundType () );
    network_.MakeUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.NetworkBoundType () );
    network_.MakePureUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, networkConst_.NetworkBoundType () );
    network_.MakeExact ();
    EXPECT_EQ ( Vertices::BoundType::exact, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.NetworkBoundType () );
}

TEST_F ( TestPowerGridPyPsaExample
       , NetworkBoundType )
{
    EXPECT_EQ ( Vertices::BoundType::unknown, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::unknown, networkConst_.NetworkBoundType () );
    network_.MakeBounded ();
    EXPECT_EQ ( Vertices::BoundType::bounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::bounded, networkConst_.NetworkBoundType () );
    network_.MakeUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::unbounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::unbounded, networkConst_.NetworkBoundType () );
    network_.MakePureUnbounded ();
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::pureunbounded, networkConst_.NetworkBoundType () );
    network_.MakeExact ();
    EXPECT_EQ ( Vertices::BoundType::exact, network_.NetworkBoundType () );
    EXPECT_EQ ( Vertices::BoundType::exact, networkConst_.NetworkBoundType () );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark NetworkType
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , NetworkType )
{
    EXPECT_THAT ( "unknown", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "unknown", StrEq( networkConst_.NetworkType () ) );
    network_.MakeBounded ();
    EXPECT_THAT ( "bounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "bounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakeUnbounded ();
    EXPECT_THAT ( "unbounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "unbounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakePureUnbounded ();
    EXPECT_THAT ( "pure_unbounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "pure_unbounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakeExact ();
    EXPECT_THAT ( "exact", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "exact", StrEq( networkConst_.NetworkType () ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , NetworkType )
{
    EXPECT_THAT ( "unknown", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "unknown", StrEq( networkConst_.NetworkType () ) );
    network_.MakeBounded ();
    EXPECT_THAT ( "bounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "bounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakeUnbounded ();
    EXPECT_THAT ( "unbounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "unbounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakePureUnbounded ();
    EXPECT_THAT ( "pure_unbounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "pure_unbounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakeExact ();
    EXPECT_THAT ( "exact", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "exact", StrEq( networkConst_.NetworkType () ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , NetworkType )
{
    EXPECT_THAT ( "unknown", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "unknown", StrEq( networkConst_.NetworkType () ) );
    network_.MakeBounded ();
    EXPECT_THAT ( "bounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "bounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakeUnbounded ();
    EXPECT_THAT ( "unbounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "unbounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakePureUnbounded ();
    EXPECT_THAT ( "pure_unbounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "pure_unbounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakeExact ();
    EXPECT_THAT ( "exact", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "exact", StrEq( networkConst_.NetworkType () ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , NetworkType )
{
    EXPECT_THAT ( "unknown", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "unknown", StrEq( networkConst_.NetworkType () ) );
    network_.MakeBounded ();
    EXPECT_THAT ( "bounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "bounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakeUnbounded ();
    EXPECT_THAT ( "unbounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "unbounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakePureUnbounded ();
    EXPECT_THAT ( "pure_unbounded", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "pure_unbounded", StrEq( networkConst_.NetworkType () ) );
    network_.MakeExact ();
    EXPECT_THAT ( "exact", StrEq( network_.NetworkType () ) );
    EXPECT_THAT ( "exact", StrEq( networkConst_.NetworkType () ) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark AddGeneratorAtUsingVertexIdAndCopyAndSwapIdiom
// ***********************************************************************
// ***********************************************************************

#ifdef EGOA_ENABLE_ASSERTION
TEST_F ( TestNetworkEmptyDeathTest
       , AddGeneratorAtUsingVertexId )
{
    TGeneratorProperties generatorProperties;
    generatorProperties.Name() = "TestGenerator1";

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddGeneratorAt"
                                                , "Graph\\(\\).VertexExists\\( vertexId \\)");
    ASSERT_DEATH ( {network_.AddGeneratorAt ( static_cast<Types::vertexId>(0)
                                            , generatorProperties );}
                 , assertionString );
}
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
TEST_F ( TestNetworkEmpty
       , AddGeneratorAtUsingVertexIdExceptionHandling )
{
    TGeneratorProperties generatorProperties;
    generatorProperties.Name() = "TestGenerator1";

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddGeneratorAt"
                                                , "Graph\\(\\).VertexExists\\( vertexId \\)");
    ASSERT_DEATH ( {network_.AddGeneratorAt ( static_cast<Types::vertexId>(0)
                                            , generatorProperties );}
                 , assertionString );
    try {
        network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );
    } catch ( std::runtime_error const & error )
    {
        EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
    } catch ( ... )
    {
        FAIL()  << "Expected std::runtime_error with message: "
                << assertionString;
    }
}
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

TEST_F ( TestNetworkEmpty
       , AddGeneratorAtUsingVertexId )
{
    TVertexProperties vertex;

    vertex.Type()                  = Vertices::to_enum<Vertices::IeeeBusType>( 99 );
    vertex.ShuntConductance()      = 0;
    vertex.ShuntSusceptance()      = 0;
    vertex.Area()                  = 0;
    vertex.VoltageMagnitude()      = 0;
    vertex.VoltageAngle()          = 0;
    vertex.NominalVoltage()        = 0;
    vertex.Zone()                  = 0;
    vertex.MaximumVoltage()        = 0;
    vertex.MinimumVoltage()        = 0;
    vertex.Status()                = Vertices::BusStatus::active;
    Types::vertexId vertexId       = network_.Graph().AddVertex( vertex );

    EXPECT_FALSE ( network_.HasGeneratorAt ( vertexId ) );

    TGeneratorProperties generatorProperties;
    generatorProperties.Name()      = "TestGenerator1";
    Types::generatorId generatorId  = network_.AddGeneratorAt(vertexId, generatorProperties);

    EXPECT_EQ ( 0,      vertexId );
    EXPECT_TRUE ( network_.HasGeneratorAt(vertexId) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId ) );
    EXPECT_EQ ( 0,      generatorId );
    EXPECT_EQ ( 1,      network_.NumberOfGenerators() );
    EXPECT_FALSE ( network_.HasGenerator( static_cast<Types::generatorId>(1) ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , AddGeneratorAtUsingVertexId )
{
    EXPECT_TRUE  ( network_.HasGeneratorAt( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGeneratorAt( static_cast<Types::vertexId>(2) ) );
    EXPECT_EQ ( 1,      network_.NumberOfGenerators() );

    TGeneratorProperties generatorProperties;
    generatorProperties.Name()       = "TestGenerator1";
    Types::generatorId generatorId1  = network_.AddGeneratorAt ( static_cast<Types::vertexId>(2)
                                                               , generatorProperties );

    EXPECT_TRUE ( network_.HasGeneratorAt( static_cast<Types::vertexId>(2) ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId1 ) );
    EXPECT_EQ ( 1,      generatorId1 );
    EXPECT_EQ ( 2,      network_.NumberOfGenerators() );

    Types::generatorId generatorId2  = network_.AddGeneratorAt ( static_cast<Types::vertexId>(0)
                                                               , generatorProperties );

    EXPECT_TRUE ( network_.HasGeneratorAt( static_cast<Types::vertexId>(0) ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId2 ) );
    EXPECT_EQ ( 2,      generatorId2 );
    EXPECT_EQ ( 3,      network_.NumberOfGenerators() );
    EXPECT_FALSE ( network_.HasGenerator( static_cast<Types::generatorId>(3) ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , AddGeneratorAtUsingVertexId )
{
    EXPECT_TRUE  ( network_.HasGeneratorAt( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGeneratorAt( static_cast<Types::vertexId>(2) ) );
    EXPECT_EQ ( 1,      network_.NumberOfGenerators() );

    TGeneratorProperties generatorProperties;
    generatorProperties.Name()       = "TestGenerator1";
    Types::generatorId generatorId1  = network_.AddGeneratorAt ( static_cast<Types::vertexId>(2)
                                                               , generatorProperties );

    EXPECT_TRUE ( network_.HasGeneratorAt( static_cast<Types::vertexId>(2) ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId1 ) );
    EXPECT_EQ ( 1,      generatorId1 );
    EXPECT_EQ ( 2,      network_.NumberOfGenerators() );

    Types::generatorId generatorId2  = network_.AddGeneratorAt ( static_cast<Types::vertexId>(0)
                                                               , generatorProperties );

    EXPECT_TRUE ( network_.HasGeneratorAt( static_cast<Types::vertexId>(0) ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId2 ) );
    EXPECT_EQ ( 2,      generatorId2 );
    EXPECT_EQ ( 3,      network_.NumberOfGenerators() );
    EXPECT_FALSE ( network_.HasGenerator( static_cast<Types::generatorId>(3) ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , AddGeneratorAtUsingVertexId )
{
    EXPECT_TRUE ( network_.HasGeneratorAt( static_cast<Types::vertexId>(0) ) );
    EXPECT_EQ ( 23,     network_.NumberOfGenerators() );

    TGeneratorProperties generatorProperties;
    generatorProperties.Name()       = "TestGenerator1";
    Types::generatorId generatorId1  = network_.AddGeneratorAt ( static_cast<Types::vertexId>(2)
                                                               , generatorProperties );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(2) ) );
    EXPECT_TRUE ( network_.HasGenerator ( generatorId1 ) );
    EXPECT_EQ ( 23,     generatorId1 );
    EXPECT_EQ ( 24,     network_.NumberOfGenerators() );

    Types::generatorId generatorId2  = network_.AddGeneratorAt ( static_cast<Types::vertexId>(0)
                                                               , generatorProperties );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_TRUE ( network_.HasGenerator ( generatorId2 ) );
    EXPECT_EQ ( 24,     generatorId2 );
    EXPECT_EQ ( 25,     network_.NumberOfGenerators() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark AddGeneratorAtUsingVertex
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , AddGeneratorAtUsingVertex )
{
    TVertexProperties vertexProperties;


    vertexProperties.Type()             = Vertices::to_enum<Vertices::IeeeBusType>( 99 );
    vertexProperties.ShuntConductance() = 0;
    vertexProperties.ShuntSusceptance() = 0;
    vertexProperties.Area()             = 0;
    vertexProperties.VoltageMagnitude() = 0;
    vertexProperties.VoltageAngle()     = 0;
    vertexProperties.NominalVoltage()   = 0;
    vertexProperties.Zone()             = 0;
    vertexProperties.MaximumVoltage()   = 0;
    vertexProperties.MinimumVoltage()   = 0;
    vertexProperties.Status()           = Vertices::BusStatus::active;
    Types::vertexId vertexId            = network_.Graph().AddVertex( vertexProperties );
    TVertex   const & vertex            = network_.Graph().VertexAt(vertexId);

    EXPECT_FALSE ( network_.HasGeneratorAt ( vertex ) );

    TGeneratorProperties generatorProperties;
    generatorProperties.Name()                = "TestGenerator1";
    Types::generatorId generatorId  = network_.AddGeneratorAt ( vertex, generatorProperties );

    EXPECT_EQ ( 0,      vertexId );
    EXPECT_TRUE ( network_.HasGeneratorAt( vertexId ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId ) );
    EXPECT_EQ ( 0,      generatorId );
    EXPECT_EQ ( 1,      network_.NumberOfGenerators() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , AddGeneratorAtUsingVertex )
{
    TVertex vertex0 = network_.Graph().VertexAt( static_cast<Types::vertexId>(0) );
    TVertex vertex3 = network_.Graph().VertexAt( static_cast<Types::vertexId>(3) );

    // Generate generator with default values
    TGeneratorProperties generatorProperties;
    generatorProperties.Name()                = "TestGenerator1";

    Types::generatorId generatorId1 = network_.AddGeneratorAt ( vertex0, generatorProperties );

    EXPECT_EQ ( 0,      network_.Graph().VertexId ( vertex0 ) );
    EXPECT_TRUE ( network_.HasGeneratorAt   ( vertex0 ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId1 ) );
    EXPECT_EQ ( 1,      generatorId1 );
    EXPECT_EQ ( 2,      network_.NumberOfGenerators() );

    Types::generatorId generatorId2 = network_.AddGeneratorAt ( vertex3, generatorProperties );

    EXPECT_EQ ( 3,      network_.Graph().VertexId ( vertex3 ) );
    EXPECT_TRUE ( network_.HasGeneratorAt   ( vertex3 ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId2 ) );
    EXPECT_EQ ( 2,      generatorId2 );
    EXPECT_EQ ( 3,      network_.NumberOfGenerators() );
    EXPECT_FALSE ( network_.HasGenerator( static_cast<Types::generatorId>(3) ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , AddGeneratorAtUsingVertex )
{
    TVertex vertex0 = network_.Graph().VertexAt( static_cast<Types::vertexId>(0) );
    TVertex vertex1 = network_.Graph().VertexAt( static_cast<Types::vertexId>(1) );

    TGeneratorProperties generatorProperties;
    generatorProperties.Name() = "TestGenerator1";
    Types::generatorId generatorId1 = network_.AddGeneratorAt ( vertex0, generatorProperties );

    EXPECT_EQ ( 0,      network_.Graph().VertexId ( vertex0 ) );
    EXPECT_TRUE ( network_.HasGeneratorAt    ( vertex0 ) );
    EXPECT_TRUE ( network_.HasGenerator ( generatorId1 ) );
    EXPECT_EQ ( 1,      generatorId1 );
    EXPECT_EQ ( 2,      network_.NumberOfGenerators() );

    Types::generatorId generatorId2 = network_.AddGeneratorAt ( vertex1, generatorProperties );

    EXPECT_EQ ( 1,      network_.Graph().VertexId ( vertex1 ) );
    EXPECT_TRUE ( network_.HasGeneratorAt   ( vertex1 ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId2 ) );
    EXPECT_EQ ( 2,      generatorId2 );
    EXPECT_EQ ( 3,      network_.NumberOfGenerators() );
    EXPECT_FALSE ( network_.HasGenerator( static_cast<Types::generatorId>(3) ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , AddGeneratorAtUsingVertex )
{
    TVertex vertex0 = network_.Graph().VertexAt( static_cast<Types::vertexId>(0) );
    TVertex vertex1 = network_.Graph().VertexAt( static_cast<Types::vertexId>(1) );

    TGeneratorProperties generatorProperties;
    generatorProperties.Name() = "TestGenerator1";
    Types::generatorId generatorId1 = network_.AddGeneratorAt ( vertex0, generatorProperties );

    EXPECT_EQ ( 0,      network_.Graph().VertexId ( vertex0 ) );
    EXPECT_TRUE ( network_.HasGeneratorAt   ( vertex0 ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId1 ) );
    EXPECT_EQ ( 23,     generatorId1 );
    EXPECT_EQ ( 24,     network_.NumberOfGenerators() );

    Types::generatorId generatorId2 = network_.AddGeneratorAt ( vertex1, generatorProperties );

    EXPECT_EQ ( 1,      network_.Graph().VertexId ( vertex1 ) );
    EXPECT_TRUE ( network_.HasGeneratorAt   ( vertex1 ) );
    EXPECT_TRUE ( network_.HasGenerator( generatorId2 ) );
    EXPECT_EQ ( 24,     generatorId2 );
    EXPECT_EQ ( 25,     network_.NumberOfGenerators() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark RemoveGeneratorAtUsingVertexIdGeneratorId
// ***********************************************************************
// ***********************************************************************

#ifdef EGOA_ENABLE_ASSERTION
TEST_F ( TestNetworkEmptyDeathTest
       , RemoveGeneratorAtUsingVertexIdGeneratorId )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                                               , static_cast<Types::generatorId>(0) );}
                 , assertionString );

    assertionString = buildAssertionString  ( "PowerGrid.hpp"
                                            , "PowerGrid"
                                            , "HasGeneratorAt"
                                            , "Graph\\(\\).VertexExists \\( vertexId \\)");
    ASSERT_DEATH ( {network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) );}, assertionString );

    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 0,       network_.NumberOfGenerators() );
}
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
TEST_F ( TestNetworkEmpty
       , RemoveGeneratorAtUsingVertexIdGeneratorIdExceptionHandling )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    try {
        network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                                   , static_cast<Types::generatorId>(0) );
    } catch ( std::runtime_error const & error )
    {
        EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
    } catch ( ... )
    {
        FAIL()  << "Expected std::runtime_error with message: "
                << assertionString;
    }

    assertionString = buildAssertionString  ( "PowerGrid.hpp"
                                            , "PowerGrid"
                                            , "HasGeneratorAt"
                                            , "Graph\\(\\).VertexExists \\( vertexId \\)");
    try {
        network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) );
    } catch ( std::runtime_error const & error )
    {
        EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
    } catch ( ... )
    {
        FAIL()  << "Expected std::runtime_error with message: "
                << assertionString;
    }

    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 0,       network_.NumberOfGenerators() );
}
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , RemoveGeneratorAtUsingVertexIdGeneratorId )
{
    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1,    network_.NumberOfGenerators() );

    network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                               , static_cast<Types::generatorId>(0) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 0,     network_.NumberOfGenerators() );
}

#ifdef EGOA_ENABLE_ASSERTION
TEST_F ( TestPowerGridAcm2018MtsfFigure4aDeathTest
       , RemoveGeneratorAtUsingVertexIdGeneratorId )
{
    EXPECT_TRUE  ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    EXPECT_TRUE  ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1,     network_.NumberOfGenerators() );

    // Vertex does not contain the generator, thus method RemoveGeneratorAt access assertion branch
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "false && \"The generatorId does not exist in generatorsAtVertex_\\[vertexId\\]!\"");
    ASSERT_DEATH ( network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(1)
                                              , static_cast<Types::generatorId>(0) )
                 , assertionString );

    EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1, network_.NumberOfGenerators() );
}
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , RemoveGeneratorAtUsingVertexIdGeneratorIdExceptionHandling )
{
    EXPECT_TRUE  ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    EXPECT_TRUE  ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1,     network_.NumberOfGenerators() );

    // Vertex does not contain the generator, thus method RemoveGeneratorAt access assertion branch
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "false && \"The generatorId does not exist in generatorsAtVertex_\\[vertexId\\]!\"");
    try {
        network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(1)
                                   , static_cast<Types::generatorId>(0) );
    } catch ( std::runtime_error const & error )
    {
        EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
    } catch ( ... )
    {
        FAIL()  << "Expected std::runtime_error with message: "
                << assertionString;
    }

    EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1, network_.NumberOfGenerators() );
}
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#ifdef EGOA_ENABLE_ASSERTION
TEST_F ( TestPowerGridAcm2018MtsfFigure4aDeathTest
       , RemoveGeneratorAtUsingGeneratorIdNonExistingVertexId )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)" );
    ASSERT_DEATH ( network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(11)
                                              , static_cast<Types::generatorId>(0) )
                 , assertionString );
}
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , RemoveGeneratorAtUsingGeneratorIdNonExistingVertexIdExceptionHandling )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)" );
    try {
        network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(11)
                                   , static_cast<Types::generatorId>(0) );
    } catch ( std::runtime_error const & error )
    {
        EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
    } catch ( ... )
    {
        FAIL()  << "Expected std::runtime_error with message: "
                << assertionString;
    }
}
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , RemoveGeneratorAtUsingVertexIdGeneratorId )
{
    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_TRUE ( network_.HasGenerator   ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1, network_.NumberOfGenerators() );

    network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                               , static_cast<Types::generatorId>(0) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 0, network_.NumberOfGenerators() );
}

#ifdef EGOA_ENABLE_ASSERTION
TEST_F ( TestPowerGridAcm2018MtsfFigure4bDeathTest
       , RemoveGeneratorAtUsingVertexIdGeneratorId )
{
    EXPECT_TRUE  ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    EXPECT_TRUE  ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1,     network_.NumberOfGenerators() );

    // Vertex has not the generator, thus method RemoveGeneratorAt access assertion branch
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "false && \"The generatorId does not exist in generatorsAtVertex_\\[vertexId\\]!\"");
    ASSERT_DEATH ( network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(1)
                                              , static_cast<Types::generatorId>(0) )
                 , assertionString );

    EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1,     network_.NumberOfGenerators() );
}
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , RemoveGeneratorAtUsingVertexIdGeneratorIdExceptionHandling )
{
    EXPECT_TRUE  ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    EXPECT_TRUE  ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1,     network_.NumberOfGenerators() );

    // Vertex has not the generator, thus method RemoveGeneratorAt access assertion branch
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "false && \"The generatorId does not exist in generatorsAtVertex_\\[vertexId\\]!\"");
    try {
        network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(1)
                                   , static_cast<Types::generatorId>(0) );
    } catch ( std::runtime_error const & error )
    {
        EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
    } catch ( ... )
    {
        FAIL()  << "Expected std::runtime_error with message: "
                << assertionString;
    }

    EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1,     network_.NumberOfGenerators() );
}
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

// ***********************************************************************
// ***********************************************************************
#pragma mark RemoveGeneratorAtUsingVertexIdGenerator
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , RemoveGeneratorAtUsingVertexIdGenerator )
{
    // Generate generator with default values
    TGeneratorProperties generatorProperties;
    generatorProperties.Name() = "TestGenerator1";

    // Vertex has no generators with assertion at RemoveGeneratorAt
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                                               , generatorProperties );}
                 , assertionString );

    // Vertex has no generators with assertion at HasGeneratorAt
    assertionString = buildAssertionString  ( "PowerGrid.hpp"
                                            , "PowerGrid"
                                            , "HasGeneratorAt"
                                            , "Graph\\(\\).VertexExists \\( vertexId \\)");
    ASSERT_DEATH ( {network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) );}, assertionString );

    EXPECT_FALSE ( network_.HasGenerator ( generatorProperties ) );
    EXPECT_EQ ( 0, network_.NumberOfGenerators() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , RemoveGeneratorAtUsingVertexIdGenerator )
{
    TGeneratorProperties & generatorProperties = network_.GeneratorAt( 0 );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_TRUE ( network_.HasGenerator   ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1, network_.NumberOfGenerators() );

    // Ordinary generator removal
    network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                               , generatorProperties );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 0,    network_.NumberOfGenerators() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4aDeathTest
       , RemoveGeneratorAtUsingVertexIdGenerator )
{
    TGeneratorProperties & generatorProperties = network_.GeneratorAt( 0 );

    // Vertex has no generators
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "false && \"The generatorId does not exist in generatorsAtVertex_\\[vertexId\\]!\"");

    ASSERT_DEATH ( {network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(1)
                                               , generatorProperties );}
                 , assertionString );

    // Ordinary generator removal
    network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                               , generatorProperties );

    // Generator does not exist
    assertionString = buildAssertionString ( "PowerGrid.hpp"
                                           , "PowerGrid"
                                           , "RemoveGeneratorAt"
                                           , "HasGenerator \\( generatorId \\)");

    ASSERT_DEATH ( {network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(1)
                                               , generatorProperties );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4aDeathTest
       , RemoveGeneratorAtUsingGeneratorNonExistingVertexId )
{
    TGeneratorProperties & generatorProperties = network_.GeneratorAt( 0 );

    // Vertex has no generators
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(11)
                                               , generatorProperties );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , RemoveGeneratorAtUsingVertexIdGenerator )
{
    TGeneratorProperties & generatorProperties = network_.GeneratorAt( 0 );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 1, network_.NumberOfGenerators() );

    // Ordinary generator removal
    network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                               , generatorProperties );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasGenerator   ( static_cast<Types::generatorId>(0) ) );
    EXPECT_EQ ( 0,    network_.NumberOfGenerators() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4bDeathTest
       , RemoveGeneratorAtUsingVertexIdGenerator )
{
    TGeneratorProperties & generatorProperties = network_.GeneratorAt( 0 );

    // Vertex has no generators
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveGeneratorAt"
                                                , "false && \"The generatorId does not exist in generatorsAtVertex_\\[vertexId\\]!\"");

    ASSERT_DEATH ( {network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(1)
                                               , generatorProperties );}
                 , assertionString );

    // Ordinary generator removal
    network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(0)
                               , generatorProperties );

    // Generator does not exist
    assertionString = buildAssertionString ( "PowerGrid.hpp"
                                           , "PowerGrid"
                                           , "RemoveGeneratorAt"
                                           , "HasGenerator \\( generatorId \\)");

    ASSERT_DEATH ( {network_.RemoveGeneratorAt ( static_cast<Types::vertexId>(1)
                                               , generatorProperties );}
                 , assertionString );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark HasGenerator
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , HasGenerator )
{
    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , HasGenerator )
{
    EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>(1) ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , HasGenerator )
{
    EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>(0) ) );
    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>(1) ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , HasGenerator )
{
    for ( Types::count counter = 0
        ; counter < network_.NumberOfGenerators()
        ; ++counter )
    {
        EXPECT_TRUE ( network_.HasGenerator ( static_cast<Types::generatorId>( counter ) ) );
    }
    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>( network_.NumberOfGenerators() ) ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , HasGeneratorAfterRemoval )
{
    EXPECT_TRUE  ( network_.HasGenerator ( static_cast<Types::generatorId>( 11 ) ) );
    network_.RemoveGeneratorAt ( static_cast<Types::vertexId>( 5 )
                               , static_cast<Types::generatorId>( 11 ) );
    EXPECT_FALSE ( network_.HasGenerator ( static_cast<Types::generatorId>( 11 ) ) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark HasGeneratorAtVertexId
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , HasGeneratorAtVertexId )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "HasGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( { network_.HasGeneratorAt ( static_cast<Types::vertexId>( 0 ) ); }
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , HasGeneratorAtVertexId )
{
    EXPECT_TRUE  ( network_.HasGeneratorAt ( static_cast<Types::vertexId>( 0 ) ) );
    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>( 1 ) ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , HasGeneratorAtVertexId )
{
    EXPECT_TRUE  ( network_.HasGeneratorAt ( static_cast<Types::vertexId>( 0 ) ) );
    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>( 1 ) ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , HasGeneratorAtVertexId )
{
    for ( Types::count counter = 0
        ; counter < network_.Graph().NumberOfVertices()
        ; ++counter )
    {
        EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>( counter ) ) );
    }
}

TEST_F ( TestPowerGridPyPsaExampleDeathTest
       , HasGeneratorAtVertexId )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "HasGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( { network_.HasGeneratorAt ( static_cast<Types::vertexId>( network_.Graph().NumberOfVertices() ) ); }
                 , assertionString );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark HasGeneratorAtVertexObject
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , HasGeneratorAtVertexObject )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "HasGeneratorAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    TVertexProperties vertexProperties;
    TVertex vertex ( 9999, vertexProperties );

    ASSERT_DEATH ( {network_.HasGeneratorAt ( vertex ); }
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , HasGeneratorAtVertexObject )
{
    TVertex vertex0 = network_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) );
    EXPECT_TRUE  ( network_.HasGeneratorAt ( vertex0 ) );
    TVertex vertex1 = network_.Graph().VertexAt( static_cast<Types::vertexId>( 1 ) );
    EXPECT_FALSE ( network_.HasGeneratorAt ( vertex1 ) );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , HasGeneratorAtVertexObject )
{
    TVertex vertex0 = network_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) );
    EXPECT_TRUE  ( network_.HasGeneratorAt ( vertex0 ) );
    TVertex vertex1 = network_.Graph().VertexAt( static_cast<Types::vertexId>( 1 ) );
    EXPECT_FALSE ( network_.HasGeneratorAt ( vertex1 ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , HasGeneratorAtVertexObject )
{
    for ( Types::count counter = 0
        ; counter < network_.Graph().NumberOfVertices()
        ; ++counter )
    {
        TVertex vertex = network_.Graph().VertexAt( static_cast<Types::vertexId>( counter ) );
        EXPECT_TRUE  ( network_.HasGeneratorAt ( vertex ) );
    }
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorId
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , GeneratorId )
{
    TGeneratorProperties generatorProperties;

    // The generator does not exist, i.e., the result should be Const::NONE
    Types::generatorId generatorId = network_.GeneratorId ( generatorProperties );

    // That's what we expect
    EXPECT_EQ ( Const::NONE, generatorId );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , GeneratorId )
{
    TGeneratorProperties generatorProperties = network_.GeneratorAt ( static_cast<Types::generatorId>( 0 ) );

    // Add generators at the vertex with identifier 0
    network_.AddGeneratorAt ( static_cast<Types::vertexId>( 0 ), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>( 0 ), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>( 0 ), generatorProperties );

    // Find the generator that was extracted from position 0
    Types::generatorId generatorId = network_.GeneratorId ( generatorProperties );

    // That's what we expect
    EXPECT_EQ ( 0, generatorId );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , GeneratorId )
{
    TGeneratorProperties generatorProperties = network_.GeneratorAt ( static_cast<Types::generatorId>( 0 ) );

    // Add generators at the vertex with identifier 0
    network_.AddGeneratorAt ( static_cast<Types::vertexId>( 0 ), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>( 0 ), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>( 0 ), generatorProperties );

    // Find the generator that was extracted from position 0
    Types::generatorId generatorId = network_.GeneratorId ( generatorProperties );

    // That's what we expect
    EXPECT_EQ ( 0, generatorId );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorIds
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , GeneratorIds )
{
    std::vector<Types::generatorId> generatorIds;

    // Vertex does not exist
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "GeneratorIds"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");
    ASSERT_DEATH ( {network_.GeneratorIds( static_cast<Types::vertexId>(0), generatorIds );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , GeneratorIds )
{
    std::vector<Types::generatorId> generatorIds;
    network_.GeneratorIds ( static_cast<Types::vertexId>(0), generatorIds );

    EXPECT_EQ ( 1, generatorIds.size() );
    EXPECT_EQ ( 0, generatorIds[0] );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , GeneratorIds )
{
    std::vector<Types::generatorId> generatorIds;
    network_.GeneratorIds ( static_cast<Types::vertexId>(0), generatorIds );

    EXPECT_EQ ( 1, generatorIds.size() );
    EXPECT_EQ ( 0, generatorIds[0] );
}

TEST_F ( TestPowerGridPyPsaExample
       , GeneratorIds )
{
    std::vector<Types::generatorId> generatorIds;
    network_.GeneratorIds ( static_cast<Types::vertexId>(0), generatorIds );

    EXPECT_EQ ( 2, generatorIds.size() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorAt
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , GeneratorAt )
{
    // Generator does not exist
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "GeneratorAt"
                                                , "HasGenerator \\( generatorId \\)");
    ASSERT_DEATH ( {network_.GeneratorAt( static_cast<Types::generatorId>(0) );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , GeneratorAt )
{
    TGeneratorProperties & generatorProperties = network_.GeneratorAt( static_cast<Types::generatorId>(0) );

    GeneratorComplyInitialValues ( generatorProperties );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , GeneratorAt )
{
    TGeneratorProperties & generatorProperties = network_.GeneratorAt( static_cast<Types::generatorId>(0) );

    GeneratorComplyInitialValues ( generatorProperties );
}

TEST_F ( TestPowerGridPyPsaExample
       , GeneratorAt )
{
    TGeneratorProperties & generatorProperties = network_.GeneratorAt( static_cast<Types::generatorId>(0) );

    GeneratorComplyInitialValues ( generatorProperties );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorsAtUsingVertexId
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , GeneratorsAtUsingVertexId )
{
    std::vector<TGeneratorProperties> generators;

    // Vertex does not exist
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "GeneratorsAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");
    ASSERT_DEATH ( {network_.GeneratorsAt( static_cast<Types::vertexId>(0), generators );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , GeneratorsAtUsingVertexId )
{
    std::vector<TGeneratorProperties> generatorProperties;
    network_.GeneratorsAt ( static_cast<Types::vertexId>(0)
                          , generatorProperties );

    EXPECT_EQ ( 1, generatorProperties.size() );
    GeneratorComplyInitialValues ( generatorProperties[0] );

    // Clear vector
    generatorProperties.clear();
    EXPECT_EQ ( 0,    generatorProperties.size() );

    // Check number of generators at vertex identifier 1
    network_.GeneratorsAt ( static_cast<Types::vertexId>(1)
                          , generatorProperties );
    EXPECT_EQ ( 0, generatorProperties.size() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , GeneratorsAtUsingVertexId )
{
    std::vector<TGeneratorProperties> generatorProperties;
    network_.GeneratorsAt ( static_cast<Types::vertexId>(0)
                          , generatorProperties );

    EXPECT_EQ ( 1, generatorProperties.size() );
    GeneratorComplyInitialValues ( generatorProperties[0] );

    // Clear vector
    generatorProperties.clear();
    EXPECT_EQ ( 0, generatorProperties.size() );

    // Check number of generators at vertex identifier 1
    network_.GeneratorsAt ( static_cast<Types::vertexId>(1)
                          , generatorProperties );
    EXPECT_EQ ( 0, generatorProperties.size() );
}

TEST_F ( TestPowerGridPyPsaExample
       , GeneratorsAtUsingVertexId )
{
    std::vector<TGeneratorProperties> generatorProperties;
    network_.GeneratorsAt ( static_cast<Types::vertexId>(0)
                          , generatorProperties );

    EXPECT_EQ ( 2, generatorProperties.size() );
    GeneratorComplyInitialValues ( generatorProperties[0] );

    // Clear vector
    generatorProperties.clear();
    EXPECT_EQ ( 0, generatorProperties.size() );

    // Check number of generators at vertex identifier 1
    network_.GeneratorsAt ( static_cast<Types::vertexId>(7)
                          , generatorProperties );
    EXPECT_EQ ( 3, generatorProperties.size() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorsAtUsingVertexObject
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , GeneratorsAtUsingVertexObject )
{
    std::vector<TGeneratorProperties> generatorProperties;

    TVertexProperties   vertexProperties;
    TVertex vertex0 ( 9999, vertexProperties );

    // Vertex does not exist
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "GeneratorsAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");
    ASSERT_DEATH ( {network_.GeneratorsAt( vertex0, generatorProperties );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , GeneratorsAtUsingVertexObject )
{
    std::vector<TGeneratorProperties> generatorProperties;

    TVertex vertex0 = network_.Graph().VertexAt ( static_cast<Types::vertexId>(0) );
    TVertex vertex1 = network_.Graph().VertexAt ( static_cast<Types::vertexId>(1) );

    network_.GeneratorsAt( vertex0, generatorProperties );

    EXPECT_EQ ( 1, generatorProperties.size() );
    GeneratorComplyInitialValues ( generatorProperties[0] );

    // Clear vector
    generatorProperties.clear();
    EXPECT_EQ ( 0, generatorProperties.size() );

    // Check number of generators at vertex identifier 1
    network_.GeneratorsAt( vertex1, generatorProperties );
    EXPECT_EQ ( 0, generatorProperties.size() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , GeneratorsAtUsingVertexObject )
{
    std::vector<TGeneratorProperties> generatorPropertiesS;

    // Generate generator with default values
    TGeneratorProperties generatorProperties;
    generatorProperties.Name() = "TestGenerator1";

    TVertex vertex0 = network_.Graph().VertexAt ( static_cast<Types::vertexId>(0) );
    TVertex vertex1 = network_.Graph().VertexAt ( static_cast<Types::vertexId>(1) );
    network_.GeneratorsAt ( vertex0, generatorPropertiesS );

    EXPECT_EQ ( 1, generatorPropertiesS.size() );
    GeneratorComplyInitialValues ( generatorPropertiesS[0] );

    // Clear vector
    generatorPropertiesS.clear();
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );
    network_.GeneratorsAt ( vertex0, generatorPropertiesS );
    EXPECT_EQ ( 4, generatorPropertiesS.size() );

    // Clear vector
    generatorPropertiesS.clear();
    EXPECT_EQ ( 0, generatorPropertiesS.size() );

    // Check number of generators at vertex identifier 1
    network_.GeneratorsAt( vertex1, generatorPropertiesS );
    EXPECT_EQ ( 0, generatorPropertiesS.size() );
}

TEST_F ( TestPowerGridPyPsaExample
       , GeneratorsAtUsingVertexObject )
{
    std::vector<TGeneratorProperties> generatorPropertiesS;

    // Generate generator with default values
    TGeneratorProperties generatorProperties;
    generatorProperties.Name() = "TestGenerator1";

    TVertex vertex0 = network_.Graph().VertexAt ( static_cast<Types::vertexId>(0) );
    TVertex vertex1 = network_.Graph().VertexAt ( static_cast<Types::vertexId>(7) );

    network_.GeneratorsAt ( vertex0, generatorPropertiesS );
    EXPECT_EQ ( 2, generatorPropertiesS.size() );

    generatorPropertiesS.clear();

    network_.GeneratorsAt ( vertex1, generatorPropertiesS );
    EXPECT_EQ ( 3, generatorPropertiesS.size() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark FindGenerator
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , FindGenerator )
{
    TGeneratorProperties              generatorProperties;
    std::vector<TGeneratorProperties> generators;

    Types::generatorId generatorId = network_.FindGenerator ( generatorProperties, generators );
    EXPECT_EQ ( Const::NONE, generatorId );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , FindGenerator )
{
    TGeneratorProperties              generatorProperties = network_.GeneratorAt ( static_cast<Types::generatorId>(0) );
    std::vector<TGeneratorProperties> generators;

    // Add generators at the vertex with identifier 0
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );

    // Get generators at a vertex with identifier 0
    network_.GeneratorsAt ( static_cast<Types::vertexId>(0), generators );

    // Find the generator that was extracted from position 0
    Types::generatorId generatorId = network_.FindGenerator ( generatorProperties, generators );

    // That's what we expect
    EXPECT_EQ ( 0, generatorId );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , FindGenerator )
{
    TGeneratorProperties              generatorProperties = network_.GeneratorAt ( static_cast<Types::generatorId>(0) );
    std::vector<TGeneratorProperties> generatorPropertiesS;

    // Add generators at the vertex with identifier 0
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );
    network_.AddGeneratorAt ( static_cast<Types::vertexId>(0), generatorProperties );

    // Get generators at a vertex with identifier 0
    network_.GeneratorsAt ( static_cast<Types::vertexId>(0), generatorPropertiesS );

    // Find the generator that was extracted from position 0
    Types::generatorId generatorId = network_.FindGenerator ( generatorProperties
                                                            , generatorPropertiesS );

    // That's what we expect
    EXPECT_EQ ( 0, generatorId );
}

TEST_F ( TestPowerGridPyPsaExample
       , FindGenerator )
{
    TGeneratorProperties              generatorProperties = network_.GeneratorAt ( static_cast<Types::generatorId>(15) );
    std::vector<TGeneratorProperties> generatorPropertiesS;

    // Get generators at a vertex with identifier 0
    network_.GeneratorsAt ( static_cast<Types::vertexId>(7)
                          , generatorPropertiesS );

    // Find the generator that was extracted from position 0
    Types::generatorId generatorId = network_.FindGenerator ( generatorProperties
                                                            , generatorPropertiesS );

    // That's what we expect: Field 0 of the vector at vertex 7
    EXPECT_EQ ( 0, generatorId );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark TotalRealPowerGenerationBoundAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , TotalRealPowerGenerationBoundAt )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalRealPowerGenerationBoundAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) ); }
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationBoundAtBounded )
{ // Bounded
    network_.MakeBounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the bounded type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 8.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationBoundAtBoundedHasNoGenerator )
{ // Bounded with no generator at that vertex
    network_.MakeBounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationBoundAtUnbounded )
{ // Unbounded
    network_.MakeUnbounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the unbounded type
    EXPECT_EQ ( 0,                  bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY,  bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationBoundAtUnboundedHasNoGenerator )
{ // Unbounded with no generator at that vertex
    network_.MakeUnbounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationBoundAtPureUnbounded )
{ // PureUnbounded
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the pure unbounded type
    EXPECT_EQ ( 0,                  bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY,  bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationBoundAtPureUnboundedHasNoGenerator )
{ // Pure unbounded with no generator at that vertex
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationBoundAtExact )
{ // Exact
    network_.MakeExact ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 1.234, bound.Minimum() );
    EXPECT_EQ ( 1.234, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationBoundAtExactHasNoGenerator )
{ // Exact with no generator at that vertex
    network_.MakeExact ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationBoundAtBounded )
{ // Bounded
    network_.MakeBounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the bounded type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 5.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationBoundAtBoundedHasNoGenerator )
{ // Bounded with no generator at that vertex
    network_.MakeBounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationBoundAtUnbounded )
{ // Unbounded
    network_.MakeUnbounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the unbounded type
    EXPECT_EQ ( 0,                  bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY,  bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationBoundAtUnboundedHasNoGenerator )
{ // Unbounded with no generator at that vertex
    network_.MakeUnbounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationBoundAtPureUnbounded )
{ // PureUnbounded
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the pure unbounded type
    EXPECT_EQ ( 0,                  bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY,  bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationBoundAtPureUnboundedHasNoGenerator )
{ // Pure unbounded with no generator at that vertex
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b, TotalRealPowerGenerationBoundAtExact )
{ // Exact
    network_.MakeExact ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationBoundAtExactHasNoGenerator )
{ // Exact with no generator at that vertex
    network_.MakeExact ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridPyPsaExample
        , TotalRealPowerGenerationBoundAtBounded )
{ // Bounded
    network_.MakeBounded ();
    TBound bound = network_.TotalRealPowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(7)
                                                                                                                                                        , static_cast<Types::index>(2) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the bounded type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( std::numeric_limits<double>::infinity(), bound.Maximum() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark TotalRealPowerGenerationAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , TotalRealPowerGenerationAt )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalRealPowerGenerationAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) ); }
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4aDeathTest
        , TotalRealPowerGenerationAtNonExistingVertex )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalRealPowerGenerationAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(9) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationAtWithVertexThatHasNoGenerator )
{
    Types::real value = network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test the total real power generation
    EXPECT_EQ ( 0.0, value );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerGenerationAt )
{
    Types::real value = network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test the total real power generation
    EXPECT_EQ ( 1.234, value );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4bDeathTest
        , TotalRealPowerGenerationAtNonExistingVertex )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalRealPowerGenerationAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(9) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationAtWithVertexThatHasNoGenerator )
{
    Types::real value = network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test the total real power generation
    EXPECT_EQ ( 0.0, value );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerGenerationAt )
{
    Types::real value = network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test the total real power generation
    EXPECT_EQ ( 0.0, value );
}

TEST_F  ( TestPowerGridPyPsaExample
        , TotalRealPowerGenerationAt )
{
    Types::real value = network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0)
                                                                                                                                                    , static_cast<Types::index>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test the total real power generation
    EXPECT_EQ ( 300.0, value );

    value = network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(8)
                                                                                                                                        , static_cast<Types::index>(0) );
    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(8) ) );
    // Test the total real power generation
    EXPECT_EQ ( 6000.0, value );

    value = network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(8)
                                                                                                                                        , static_cast<Types::index>(0) );
    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(8) ) );
    // Test the total real power generation
    EXPECT_EQ ( 6000.0, value );

    value = network_.TotalRealPowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(7)
                                                                                                                                        , static_cast<Types::index>(6) );
    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(7) ) );
    // Test the total real power generation
    EXPECT_EQ ( 5280.0, value );
}


// ***********************************************************************
// ***********************************************************************
#pragma mark TotalReactivePowerGenerationBoundAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , TotalReactivePowerGenerationBoundAt )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalReactivePowerGenerationBoundAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) ); }
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationBoundAtBounded )
{ // Bounded
    network_.MakeBounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the bounded type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 2.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationBoundAtBoundedHasNoGenerator )
{ // Bounded with no generator at that vertex
    network_.MakeBounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationBoundAtUnbounded )
{ // Unbounded
    network_.MakeUnbounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the unbounded type
    EXPECT_EQ ( 0,                  bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY,  bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationBoundAtUnboundedHasNoGenerator )
{ // Unbounded with no generator at that vertex
    network_.MakeUnbounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationBoundAtPureUnbounded )
{ // PureUnbounded
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the pure unbounded type
    EXPECT_EQ ( 0,                  bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY,  bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationBoundAtPureUnboundedHasNoGenerator )
{ // Pure unbounded with no generator at that vertex
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationBoundAtExact )
{ // Exact
    network_.MakeExact ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 1.111, bound.Minimum() );
    EXPECT_EQ ( 1.111, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationBoundAtExactHasNoGenerator )
{ // Exact with no generator at that vertex
    network_.MakeExact ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationBoundAtBounded )
{ // Bounded
    network_.MakeBounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the bounded type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationBoundAtBoundedHasNoGenerator )
{ // Bounded with no generator at that vertex
    network_.MakeBounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationBoundAtUnbounded )
{ // Unbounded
    network_.MakeUnbounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the unbounded type
    EXPECT_EQ ( 0,                  bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY,  bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationBoundAtUnboundedHasNoGenerator )
{ // Unbounded with no generator at that vertex
    network_.MakeUnbounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationBoundAtPureUnbounded )
{ // PureUnbounded
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the pure unbounded type
    EXPECT_EQ ( 0,                  bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY,  bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationBoundAtPureUnboundedHasNoGenerator )
{ // Pure unbounded with no generator at that vertex
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , TotalReactivePowerGenerationBoundAtExact )
{ // Exact
    network_.MakeExact ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationBoundAtExactHasNoGenerator )
{ // Exact with no generator at that vertex
    network_.MakeExact ();
    TBound bound = network_.TotalReactivePowerGenerationBoundAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test bound for the exact type
    EXPECT_EQ ( 0.0, bound.Minimum() );
    EXPECT_EQ ( 0.0, bound.Maximum() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark TotalReactivePowerGenerationAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , TotalReactivePowerGenerationAt )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalReactivePowerGenerationAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalReactivePowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) ); }
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4aDeathTest
        , TotalReactivePowerGenerationAtNonExistingVertex )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalReactivePowerGenerationAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalReactivePowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(9) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationAtWithVertexThatHasNoGenerator )
{
    Types::real value = network_.TotalReactivePowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test the total real power generation
    EXPECT_EQ ( 0.0, value );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalReactivePowerGenerationAt )
{
    Types::real value = network_.TotalReactivePowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test the total real power generation
    EXPECT_EQ ( 1.111, value );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4bDeathTest
        , TotalReactivePowerGenerationAtNonExistingVertex )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalReactivePowerGenerationAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalReactivePowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(9) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationAtWithVertexThatHasNoGenerator )
{
    Types::real value = network_.TotalReactivePowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(1) );

    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );
    // Test the total real power generation
    EXPECT_EQ ( 0.0, value );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalReactivePowerGenerationAt )
{
    Types::real value = network_.TotalReactivePowerGenerationAt<Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> ( static_cast<Types::vertexId>(0) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test the total real power generation
    EXPECT_EQ ( 0.0, value );
}

TEST_F  ( TestPowerGridPyPsaExample
        , TotalReactivePowerGenerationAt )
{
    Types::real value = network_.TotalReactivePowerGenerationAt<
                                Vertices::GenerationStrategyDifferentiationType
                                            ::totalVertexPowerGenerationPerSnapshot > ( static_cast<Types::vertexId>( 0 ) );

    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(0) ) );
    // Test the total real power generation
    EXPECT_EQ ( 0.0, value );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark AddLoadAtVertexId
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , AddLoadAtUsingVertexId )
{
    TLoadProperties loadProperties;

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddLoadAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.AddLoadAt ( static_cast<Types::vertexId>(0), loadProperties ); }
                 , assertionString );
}

TEST_F  ( TestNetworkEmpty
        , AddLoadAtUsingVertexId )
{
    // Add vertex
    TVertexProperties vertexProperties;
    Types::vertexId vertexId = network_.Graph().AddVertex ( vertexProperties );
    EXPECT_EQ    ( 0, network_.NumberOfLoads() );
    EXPECT_FALSE ( network_.HasLoadAt ( vertexId ) );

    // Add load at vertex
    TLoadProperties loadProperties;
    loadProperties.Name() = "TestLoad1";
    Types::loadId loadId = network_.AddLoadAt ( vertexId, loadProperties );
    // Check
    EXPECT_EQ   ( 0, vertexId );
    EXPECT_TRUE ( network_.HasLoadAt ( vertexId ) );
    EXPECT_TRUE ( network_.HasLoad ( loadId ) );
    EXPECT_EQ   ( 0, loadId );
    EXPECT_EQ   ( 1, network_.NumberOfLoads() );
    EXPECT_FALSE( network_.HasLoad ( static_cast<Types::loadId>(1) ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4aDeathTest
        , AddLoadAtUsingVertexIdNonExistingVertexId )
{
    TLoadProperties loadProperties;
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddLoadAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.AddLoadAt ( static_cast<Types::vertexId>(9), loadProperties );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , AddLoadAtUsingVertexId )
{
    Types::vertexId vertexId = static_cast<Types::vertexId>(2);
    EXPECT_EQ    ( 1, network_.NumberOfLoads() );
    EXPECT_FALSE ( network_.HasLoadAt ( vertexId ) );
    // Add load at vertex 2
    TLoadProperties loadProperties;
    Types::loadId   loadId   = network_.AddLoadAt ( vertexId, loadProperties );
    // Check
    EXPECT_TRUE  ( network_.HasLoadAt ( vertexId ) );
    EXPECT_TRUE  ( network_.HasLoad   ( loadId   ) );
    EXPECT_EQ    ( 1, loadId );
    EXPECT_EQ    ( 2, network_.NumberOfLoads() );
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , AddLoadAtUsingVertexId )
{
    Types::vertexId vertexId = static_cast<Types::vertexId>(1);
    EXPECT_EQ    ( 1, network_.NumberOfLoads() );
    EXPECT_FALSE ( network_.HasLoadAt ( vertexId ) );
    // Add load at vertex 2
    TLoadProperties loadProperties;
    Types::loadId   loadId   = network_.AddLoadAt ( vertexId, loadProperties );
    // Check
    EXPECT_TRUE  ( network_.HasLoadAt ( vertexId ) );
    EXPECT_TRUE  ( network_.HasLoad   ( loadId   ) );
    EXPECT_EQ    ( 1, loadId );
    EXPECT_EQ    ( 2, network_.NumberOfLoads() );
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(2) ) );

    loadId   = network_.AddLoadAt ( vertexId, loadProperties );
    EXPECT_EQ    ( 3, network_.NumberOfLoads() );
    EXPECT_EQ    ( 2, loadId );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark AddLoadAtVertexObject
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , AddLoadAtVertexObject )
{
    TLoadProperties loadProperties;
    TVertexProperties vertexProperties;
    TVertex vertex ( 9999, vertexProperties );

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddLoadAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.AddLoadAt ( vertex, loadProperties ); }
                 , assertionString );
}

TEST_F  ( TestNetworkEmpty
        , AddLoadAtVertexObject )
{
    TVertexProperties vertexProperties;
    Types::vertexId   vertexId = network_.Graph().AddVertex ( vertexProperties );
    TVertex           vertex   = network_.Graph().VertexAt  ( vertexId );
                      vertex   = networkConst_.Graph().VertexAt  ( vertexId );

    TLoadProperties loadProperties;
    loadProperties.Name() = "TestLoad1";
    Types::loadId loadId  = network_.AddLoadAt ( vertex, loadProperties );

    EXPECT_EQ   ( 0, vertexId );
    EXPECT_TRUE ( network_.HasLoadAt ( vertex ) );
    EXPECT_TRUE ( networkConst_.HasLoadAt ( vertex ) );
    EXPECT_TRUE ( network_.HasLoad ( loadId ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( loadId ) );
    EXPECT_EQ   ( 0, loadId );
    EXPECT_EQ   ( 1, network_.NumberOfLoads() );
    EXPECT_EQ   ( 1, networkConst_.NumberOfLoads() );
    EXPECT_FALSE( network_.HasLoad ( static_cast<Types::loadId>(1) ) );
    EXPECT_FALSE( networkConst_.HasLoad ( static_cast<Types::loadId>(1) ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , AddLoadAtVertexObject )
{
    TVertex vertex = network_.Graph().VertexAt ( static_cast<Types::vertexId>(2) );
    EXPECT_FALSE ( network_.HasLoadAt ( vertex ) );

    vertex = networkConst_.Graph().VertexAt ( static_cast<Types::vertexId>(2) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( vertex ) );

    EXPECT_EQ    ( 1, network_.NumberOfLoads() );
    EXPECT_EQ    ( 1, networkConst_.NumberOfLoads() );

    // Add load at vertex 2
    TLoadProperties loadProperties;
    Types::loadId   loadId   = network_.AddLoadAt ( vertex, loadProperties );
    // Check
    EXPECT_TRUE  ( network_.HasLoadAt ( vertex ) );
    EXPECT_TRUE  ( networkConst_.HasLoadAt ( vertex ) );
    EXPECT_TRUE  ( network_.HasLoad   ( loadId   ) );
    EXPECT_TRUE  ( networkConst_.HasLoad   ( loadId   ) );
    EXPECT_EQ    ( 1, loadId );
    EXPECT_EQ    ( 2, network_.NumberOfLoads() );
    EXPECT_EQ    ( 2, networkConst_.NumberOfLoads() );
    EXPECT_TRUE  ( network_.HasLoadAt ( vertex ) );
    EXPECT_TRUE  ( networkConst_.HasLoadAt ( vertex ) );
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );
    EXPECT_TRUE  ( network_.HasLoadAt ( static_cast<Types::vertexId>(3) ) );
    EXPECT_TRUE  ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(3) ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , AddLoadAtVertexObject )
{
    TVertex vertex = network_.Graph().VertexAt ( static_cast<Types::vertexId>(1) );
    EXPECT_FALSE ( network_.HasLoadAt ( vertex ) );

    vertex = networkConst_.Graph().VertexAt ( static_cast<Types::vertexId>(1) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( vertex ) );

    EXPECT_EQ    ( 1, network_.NumberOfLoads() );
    EXPECT_EQ    ( 1, networkConst_.NumberOfLoads() );
    // Add load at vertex 2
    TLoadProperties loadProperties;
    Types::loadId   loadId   = network_.AddLoadAt ( vertex, loadProperties );
    // Check
    EXPECT_TRUE  ( network_.HasLoadAt ( vertex ) );
    EXPECT_TRUE  ( networkConst_.HasLoadAt ( vertex ) );
    EXPECT_TRUE  ( network_.HasLoad   ( loadId   ) );
    EXPECT_TRUE  ( networkConst_.HasLoad   ( loadId   ) );
    EXPECT_EQ    ( 1, loadId );
    EXPECT_EQ    ( 2, network_.NumberOfLoads() );
    EXPECT_EQ    ( 2, networkConst_.NumberOfLoads() );
    EXPECT_TRUE  ( network_.HasLoadAt ( vertex ) );
    EXPECT_TRUE  ( networkConst_.HasLoadAt ( vertex ) );
    EXPECT_FALSE ( network_.HasLoadAt ( network_.Graph().VertexAt ( static_cast<Types::vertexId>(0) ) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( networkConst_.Graph().VertexAt ( static_cast<Types::vertexId>(0) ) ) );
    EXPECT_FALSE ( network_.HasLoadAt ( network_.Graph().VertexAt ( static_cast<Types::vertexId>(2) ) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( networkConst_.Graph().VertexAt ( static_cast<Types::vertexId>(2) ) ) );
    EXPECT_TRUE  ( network_.HasLoadAt ( network_.Graph().VertexAt ( static_cast<Types::vertexId>(3) ) ) );
    EXPECT_TRUE  ( networkConst_.HasLoadAt ( networkConst_.Graph().VertexAt ( static_cast<Types::vertexId>(3) ) ) );

    loadId   = network_.AddLoadAt ( vertex, loadProperties );
    EXPECT_EQ    ( 3, network_.NumberOfLoads() );
    EXPECT_EQ    ( 3, networkConst_.NumberOfLoads() );
    EXPECT_EQ    ( 2, loadId );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark RemoveLoadAtVertexId
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , RemoveLoadAtUsingVertexIdLoadId )
{
    EXPECT_EQ ( 0, network_.NumberOfLoads() );
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveLoadAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.RemoveLoadAt ( static_cast<Types::vertexId>(0)
                                          , static_cast<Types::loadId>(0) );}
                 , assertionString );

    assertionString = buildAssertionString  ( "PowerGrid.hpp"
                                            , "PowerGrid"
                                            , "HasLoadAt"
                                            , "Graph\\(\\).VertexExists \\( vertexId \\)");
    ASSERT_DEATH ( {network_.HasLoadAt ( static_cast<Types::vertexId>(0) );}, assertionString );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(0) ) );
    EXPECT_EQ ( 0, network_.NumberOfLoads() );
}

TEST_F  ( TestNetworkEmptyDeathTest
        , RemoveLoadAtUsingVertexIdWhereLoadIdDoesNotExists )
{
    TVertexProperties vertexProperties;
    Types::vertexId   vertexId = network_.Graph().AddVertex ( vertexProperties );
    TVertex   const & vertex   = network_.Graph().VertexAt  ( vertexId );

    EXPECT_EQ ( 0, network_.NumberOfLoads() );

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RemoveLoadAt"
                                                , "HasLoad \\( loadId \\)");

    ASSERT_DEATH ( {network_.RemoveLoadAt ( vertexId
                                          , static_cast<Types::loadId>(0) );}
                 , assertionString );
    EXPECT_EQ ( 0, network_.NumberOfLoads() );
}

TEST_F  ( TestNetworkEmptyDeathTest
        , RemoveLoadAtUsingVertexIdLoadIdAddingAndRemovingMultipleLoads )
{
    TVertexProperties vertexProperties;
    TLoadProperties loadProperties;

    // Add vertex
    Types::vertexId vertexId = network_.Graph().AddVertex ( vertexProperties );
    TVertex const & vertex   = network_.Graph().VertexAt  ( vertexId );

    EXPECT_FALSE  ( network_.HasLoadAt ( vertex ) );
    // Add multiple loads
    Types::loadId   loadId0   = network_.AddLoadAt ( vertexId, loadProperties );
    Types::loadId   loadId1   = network_.AddLoadAt ( vertexId, loadProperties );
    Types::loadId   loadId2   = network_.AddLoadAt ( vertexId, loadProperties );
    Types::loadId   loadId3   = network_.AddLoadAt ( vertexId, loadProperties );
    Types::loadId   loadId4   = network_.AddLoadAt ( vertexId, loadProperties );
    EXPECT_EQ   ( 5, network_.NumberOfLoads() ) ;
    EXPECT_TRUE ( network_.HasLoadAt ( vertex ) );
    EXPECT_TRUE ( network_.HasLoad ( loadId0 ) );
    EXPECT_TRUE ( network_.HasLoad ( loadId1 ) );
    EXPECT_TRUE ( network_.HasLoad ( loadId2 ) );
    EXPECT_TRUE ( network_.HasLoad ( loadId3 ) );
    EXPECT_TRUE ( network_.HasLoad ( loadId4 ) );
    EXPECT_EQ    ( 0, loadId0 );
    EXPECT_EQ    ( 1, loadId1 );
    EXPECT_EQ    ( 2, loadId2 );
    EXPECT_EQ    ( 3, loadId3 );
    EXPECT_EQ    ( 4, loadId4 );
    // Remove some loads
    network_.RemoveLoadAt ( vertexId, loadId0 );
    network_.RemoveLoadAt ( vertexId, loadId3 );
    EXPECT_EQ ( 3, network_.NumberOfLoads() ) ;
    EXPECT_FALSE ( network_.HasLoad ( loadId0 ) );
    EXPECT_TRUE  ( network_.HasLoad ( loadId1 ) );
    EXPECT_TRUE  ( network_.HasLoad ( loadId2 ) );
    EXPECT_FALSE ( network_.HasLoad ( loadId3 ) );
    EXPECT_TRUE  ( network_.HasLoad ( loadId4 ) );
    // Remove the rest
    network_.RemoveLoadAt ( vertexId, loadId1 );
    network_.RemoveLoadAt ( vertexId, loadId2 );
    network_.RemoveLoadAt ( vertexId, loadId4 );
    EXPECT_EQ ( 0, network_.NumberOfLoads() ) ;
    EXPECT_FALSE  ( network_.HasLoadAt ( vertex ) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark HasLoadId
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmpty
        , HasLoadId )
{
    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(0) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(0) ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , HasLoadId )
{ // Checks loadId
    EXPECT_TRUE ( network_.HasLoad ( static_cast<Types::loadId>(0) ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( static_cast<Types::loadId>(0) ) );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(1) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(1) ) );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(2) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(2) ) );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(3) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(3) ) );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(9999) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(9999) ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , HasLoadId )
{ // Checks loadId
    EXPECT_TRUE ( network_.HasLoad ( static_cast<Types::loadId>(0) ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( static_cast<Types::loadId>(0) ) );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(1) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(1) ) );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(2) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(2) ) );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(3) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(3) ) );

    EXPECT_FALSE ( network_.HasLoad ( static_cast<Types::loadId>(9999) ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( static_cast<Types::loadId>(9999) ) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark HasLoadObject
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmpty
        , HasLoadObject )
{
    TLoadProperties loadProperties;
    EXPECT_FALSE ( network_.HasLoad ( loadProperties ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( loadProperties ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , HasLoadObject )
{ // Checks loadObject
    TLoadProperties loadProperties0;
    EXPECT_FALSE ( network_.HasLoad ( loadProperties0 ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( loadProperties0 ) );

    EXPECT_TRUE ( network_.HasLoad ( static_cast<Types::loadId>(0) ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( static_cast<Types::loadId>(0) ) );
    TLoadProperties loadProperties1 = network_.LoadAt( 0 );
    EXPECT_TRUE ( network_.HasLoad ( loadProperties1 ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( loadProperties1 ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , HasLoadObject )
{ // Checks loadObject
    TLoadProperties loadProperties0;
    EXPECT_FALSE ( network_.HasLoad ( loadProperties0 ) );
    EXPECT_FALSE ( networkConst_.HasLoad ( loadProperties0 ) );

    EXPECT_TRUE ( network_.HasLoad ( static_cast<Types::loadId>(0) ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( static_cast<Types::loadId>(0) ) );

    TLoadProperties loadProperties1 = network_.LoadAt( 0 );
    EXPECT_TRUE ( network_.HasLoad ( loadProperties1 ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( loadProperties1 ) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark HasLoadAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , HasLoadAt )
{ // Checks if there is a load at a vertex

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "HasLoadAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.HasLoadAt ( static_cast<Types::vertexId>(0) );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.HasLoadAt ( static_cast<Types::vertexId>(0) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , HasLoadAt )
{ // Checks if there is a load at a vertex
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(0) ) );

    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );

    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(2) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(2) ) );

    EXPECT_TRUE  ( network_.HasLoadAt ( static_cast<Types::vertexId>(3) ) );
    EXPECT_TRUE  ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(3) ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , HasLoadAt )
{ // Checks if there is a load at a vertex
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(0) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(0) ) );

    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );

    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(2) ) );
    EXPECT_FALSE ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(2) ) );

    EXPECT_TRUE  ( network_.HasLoadAt ( static_cast<Types::vertexId>(3) ) );
    EXPECT_TRUE  ( networkConst_.HasLoadAt ( static_cast<Types::vertexId>(3) ) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark LoadId
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , LoadId )
{ // Checks if there is a load at a vertex

    TLoadProperties loadProperties0;

    EXPECT_EQ ( Const::NONE, network_.LoadId ( loadProperties0 ) );
    EXPECT_EQ ( Const::NONE, networkConst_.LoadId ( loadProperties0 ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , LoadId )
{ // Checks if there is a load at a vertex
    TLoadProperties loadProperties0;
    EXPECT_EQ ( Const::NONE, network_.LoadId ( loadProperties0 ) );
    EXPECT_EQ ( Const::NONE, networkConst_.LoadId ( loadProperties0 ) );

    EXPECT_TRUE ( network_.HasLoad ( static_cast<Types::loadId>(0) ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( static_cast<Types::loadId>(0) ) );

    TLoadProperties loadProperties1 = network_.LoadAt( 0 );
    EXPECT_EQ ( 0, network_.LoadId ( loadProperties1 ) );

    loadProperties1 = networkConst_.LoadAt( 0 );
    EXPECT_EQ ( 0, networkConst_.LoadId ( loadProperties1 ) );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , LoadId )
{ // Checks if there is a load at a vertex
    TLoadProperties loadProperties0;
    EXPECT_EQ ( Const::NONE, network_.LoadId ( loadProperties0 ) );
    EXPECT_EQ ( Const::NONE, networkConst_.LoadId ( loadProperties0 ) );

    EXPECT_TRUE ( network_.HasLoad ( static_cast<Types::loadId>(0) ) );
    EXPECT_TRUE ( networkConst_.HasLoad ( static_cast<Types::loadId>(0) ) );

    TLoadProperties loadProperties1 = network_.LoadAt( 0 );
    EXPECT_EQ ( 0, network_.LoadId ( loadProperties1 ) );

    loadProperties1 = networkConst_.LoadAt( 0 );
    EXPECT_EQ ( 0, networkConst_.LoadId ( loadProperties1 ) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark LoadIds
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , LoadIds )
{ // Checks if there is a load at a vertex

    TLoadProperties             loadProperties0;
    std::vector<Types::loadId>  loadIds;

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "LoadIds"
                                                , "Graph\\(\\).VertexExists\\( vertexId \\)");

    ASSERT_DEATH ( {network_.LoadIds ( static_cast<Types::vertexId>( 0 ), loadIds );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.LoadIds ( static_cast<Types::vertexId>( 0 ), loadIds );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , LoadIds )
{ // Checks if there is a load at a vertex
    TLoadProperties             loadProperties0;
    std::vector<Types::loadId>  loadIds;

    network_.LoadIds ( static_cast<Types::vertexId>( 0 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );
    networkConst_.LoadIds ( static_cast<Types::vertexId>( 0 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );

    network_.LoadIds ( static_cast<Types::vertexId>( 1 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );
    networkConst_.LoadIds ( static_cast<Types::vertexId>( 1 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );

    network_.LoadIds ( static_cast<Types::vertexId>( 2 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );
    networkConst_.LoadIds ( static_cast<Types::vertexId>( 2 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );

    network_.LoadIds ( static_cast<Types::vertexId>( 3 ), loadIds );
    EXPECT_EQ ( 1, loadIds.size() );
    loadIds.clear();
    networkConst_.LoadIds ( static_cast<Types::vertexId>( 3 ), loadIds );
    EXPECT_EQ ( 1, loadIds.size() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , LoadIds )
{ // Checks if there is a load at a vertex
    TLoadProperties             loadProperties0;
    std::vector<Types::loadId>  loadIds;

    network_.LoadIds ( static_cast<Types::vertexId>( 0 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );
    networkConst_.LoadIds ( static_cast<Types::vertexId>( 0 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );

    network_.LoadIds ( static_cast<Types::vertexId>( 1 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );
    networkConst_.LoadIds ( static_cast<Types::vertexId>( 1 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );

    network_.LoadIds ( static_cast<Types::vertexId>( 2 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );
    networkConst_.LoadIds ( static_cast<Types::vertexId>( 2 ), loadIds );
    EXPECT_EQ ( 0, loadIds.size() );

    network_.LoadIds ( static_cast<Types::vertexId>( 3 ), loadIds );
    EXPECT_EQ ( 1, loadIds.size() );
    loadIds.clear();
    networkConst_.LoadIds ( static_cast<Types::vertexId>( 3 ), loadIds );
    EXPECT_EQ ( 1, loadIds.size() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark LoadAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , LoadAt )
{ // Checks if there is a load at a load ID
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "LoadAt"
                                                , "HasLoad \\( loadId \\)");

    ASSERT_DEATH ( {network_.LoadAt ( static_cast<Types::loadId>( 0 ) );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.LoadAt ( static_cast<Types::loadId>( 0 ) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4aDeathTest
        , LoadAt )
{ // Checks if there is a load at a load ID and returns the property
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "LoadAt"
                                                , "HasLoad \\( loadId \\)");

    ASSERT_DEATH ( {network_.LoadAt ( static_cast<Types::loadId>( 3 ) );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.LoadAt ( static_cast<Types::loadId>( 3 ) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , LoadAt )
{ // Checks if there is a load at a load ID and returns the property
    TLoadProperties loadProperties0 = network_.LoadAt ( static_cast<Types::loadId>( 0 ) );

    EXPECT_EQ ( "4", loadProperties0.Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, loadProperties0.Type() );
    EXPECT_EQ ( 8.0, loadProperties0.RealPowerLoad() );
    EXPECT_EQ ( 0.0, loadProperties0.RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 8.0, loadProperties0.RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 1.1, loadProperties0.ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, loadProperties0.ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 1.1, loadProperties0.ReactivePowerLoadBound().Maximum() );

    loadProperties0 = networkConst_.LoadAt ( static_cast<Types::loadId>( 0 ) );

    EXPECT_EQ ( "4", loadProperties0.Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, loadProperties0.Type() );
    EXPECT_EQ ( 8.0, loadProperties0.RealPowerLoad() );
    EXPECT_EQ ( 0.0, loadProperties0.RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 8.0, loadProperties0.RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 1.1, loadProperties0.ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, loadProperties0.ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 1.1, loadProperties0.ReactivePowerLoadBound().Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4bDeathTest
        , LoadAt )
{ // Checks if there is a load at a load ID and returns the property
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "LoadAt"
                                                , "HasLoad \\( loadId \\)");

    ASSERT_DEATH ( {network_.LoadAt ( static_cast<Types::loadId>( 3 ) );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.LoadAt ( static_cast<Types::loadId>( 3 ) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , LoadAt )
{ // Checks if there is a load at a load ID and returns the property
    TLoadProperties loadProperties0 = network_.LoadAt ( static_cast<Types::loadId>( 0 ) );

    EXPECT_EQ ( "4", loadProperties0.Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, loadProperties0.Type() );
    EXPECT_EQ ( 5.0, loadProperties0.RealPowerLoad() );
    EXPECT_EQ ( 0.0, loadProperties0.RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 5.0, loadProperties0.RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 0.0, loadProperties0.ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, loadProperties0.ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 0.0, loadProperties0.ReactivePowerLoadBound().Maximum() );

    loadProperties0 = networkConst_.LoadAt ( static_cast<Types::loadId>( 0 ) );

    EXPECT_EQ ( "4", loadProperties0.Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, loadProperties0.Type() );
    EXPECT_EQ ( 5.0, loadProperties0.RealPowerLoad() );
    EXPECT_EQ ( 0.0, loadProperties0.RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 5.0, loadProperties0.RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 0.0, loadProperties0.ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, loadProperties0.ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 0.0, loadProperties0.ReactivePowerLoadBound().Maximum() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark LoadsAtVertexId
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , LoadsAtVertexId )
{ // Return load properties at a vertex ID
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "LoadsAt"
                                                , "Graph\\(\\).VertexExists\\( vertexId \\)");

    std::vector<TLoadProperties> loads;
    ASSERT_DEATH ( {network_.LoadsAt ( static_cast<Types::vertexId>( 0 ), loads );}
                 , assertionString );

    ASSERT_DEATH ( {networkConst_.LoadsAt ( static_cast<Types::vertexId>( 0 ), loads );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , LoadsAtVertexId )
{ // Return load properties at a vertex ID
    std::vector<TLoadProperties> multipleLoadProperties;

    network_.LoadsAt ( static_cast<Types::vertexId>( 0 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( static_cast<Types::vertexId>( 0 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( static_cast<Types::vertexId>( 1 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( static_cast<Types::vertexId>( 1 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( static_cast<Types::vertexId>( 2 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( static_cast<Types::vertexId>( 2 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( static_cast<Types::vertexId>( 3 ), multipleLoadProperties );
    EXPECT_EQ ( 1, multipleLoadProperties.size() );

    EXPECT_EQ ( "4", multipleLoadProperties[0].Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, multipleLoadProperties[0].Type() );
    EXPECT_EQ ( 8.0, multipleLoadProperties[0].RealPowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 8.0, multipleLoadProperties[0].RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 1.1, multipleLoadProperties[0].ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 1.1, multipleLoadProperties[0].ReactivePowerLoadBound().Maximum() );
    multipleLoadProperties.clear();

    networkConst_.LoadsAt ( static_cast<Types::vertexId>( 3 ), multipleLoadProperties );
    EXPECT_EQ ( 1, multipleLoadProperties.size() );

    EXPECT_EQ ( "4", multipleLoadProperties[0].Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, multipleLoadProperties[0].Type() );
    EXPECT_EQ ( 8.0, multipleLoadProperties[0].RealPowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 8.0, multipleLoadProperties[0].RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 1.1, multipleLoadProperties[0].ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 1.1, multipleLoadProperties[0].ReactivePowerLoadBound().Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , LoadsAtVertexId )
{ // Return load properties at a vertex ID
    std::vector<TLoadProperties> multipleLoadProperties;

    network_.LoadsAt ( static_cast<Types::vertexId>( 0 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( static_cast<Types::vertexId>( 0 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( static_cast<Types::vertexId>( 1 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( static_cast<Types::vertexId>( 1 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( static_cast<Types::vertexId>( 2 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( static_cast<Types::vertexId>( 2 ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( static_cast<Types::vertexId>( 3 ), multipleLoadProperties );
    EXPECT_EQ ( 1, multipleLoadProperties.size() );

    EXPECT_EQ ( "4", multipleLoadProperties[0].Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, multipleLoadProperties[0].Type() );
    EXPECT_EQ ( 5.0, multipleLoadProperties[0].RealPowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 5.0, multipleLoadProperties[0].RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Maximum() );
    multipleLoadProperties.clear();

    networkConst_.LoadsAt ( static_cast<Types::vertexId>( 3 ), multipleLoadProperties );
    EXPECT_EQ ( 1, multipleLoadProperties.size() );

    EXPECT_EQ ( "4", multipleLoadProperties[0].Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, multipleLoadProperties[0].Type() );
    EXPECT_EQ ( 5.0, multipleLoadProperties[0].RealPowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 5.0, multipleLoadProperties[0].RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Maximum() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark LoadsAtVertex
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , LoadsAtVertex )
{ // Return load properties at a vertex ID
    auto assertionString = buildAssertionString ( "StaticGraph.hpp"
                                                , "StaticGraph"
                                                , "VertexAt"
                                                , "VertexExists\\(id\\)");

    std::vector<TLoadProperties> loads;
    ASSERT_DEATH ( {network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), loads );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), loads );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , LoadsAtVertex )
{ // Return load properties at a vertex ID
    std::vector<TLoadProperties> multipleLoadProperties;

    network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 1 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 1 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 2 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 2 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 3 ) ), multipleLoadProperties );
    EXPECT_EQ ( 1, multipleLoadProperties.size() );

    EXPECT_EQ ( "4", multipleLoadProperties[0].Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, multipleLoadProperties[0].Type() );
    EXPECT_EQ ( 8.0, multipleLoadProperties[0].RealPowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 8.0, multipleLoadProperties[0].RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 1.1, multipleLoadProperties[0].ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 1.1, multipleLoadProperties[0].ReactivePowerLoadBound().Maximum() );
    multipleLoadProperties.clear();

    networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 3 ) ), multipleLoadProperties );
    EXPECT_EQ ( 1, multipleLoadProperties.size() );

    EXPECT_EQ ( "4", multipleLoadProperties[0].Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, multipleLoadProperties[0].Type() );
    EXPECT_EQ ( 8.0, multipleLoadProperties[0].RealPowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 8.0, multipleLoadProperties[0].RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 1.1, multipleLoadProperties[0].ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 1.1, multipleLoadProperties[0].ReactivePowerLoadBound().Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , LoadsAtVertex )
{ // Return load properties at a vertex ID
    std::vector<TLoadProperties> multipleLoadProperties;

    network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 1 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 1 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 2 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );
    networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 2 ) ), multipleLoadProperties );
    EXPECT_EQ ( 0, multipleLoadProperties.size() );

    network_.LoadsAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 3 ) ), multipleLoadProperties );
    EXPECT_EQ ( 1, multipleLoadProperties.size() );
    EXPECT_EQ ( "4", multipleLoadProperties[0].Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, multipleLoadProperties[0].Type() );
    EXPECT_EQ ( 5.0, multipleLoadProperties[0].RealPowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 5.0, multipleLoadProperties[0].RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Maximum() );
    multipleLoadProperties.clear();

    networkConst_.LoadsAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 3 ) ), multipleLoadProperties );
    EXPECT_EQ ( 1, multipleLoadProperties.size() );

    EXPECT_EQ ( "4", multipleLoadProperties[0].Name() );
    EXPECT_EQ ( Vertices::IeeeBusType::load, multipleLoadProperties[0].Type() );
    EXPECT_EQ ( 5.0, multipleLoadProperties[0].RealPowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].RealPowerLoadBound().Minimum() );
    EXPECT_EQ ( 5.0, multipleLoadProperties[0].RealPowerLoadBound().Maximum() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoad() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Minimum() );
    EXPECT_EQ ( 0.0, multipleLoadProperties[0].ReactivePowerLoadBound().Maximum() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark RealPowerLoadAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , RealPowerLoadAt )
{ // Total real power load for a snapshot (here 0 implicitly) for a vertexId
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "RealPowerLoadAt"
                                                , "Graph\\(\\).VertexExists\\( vertexId \\)");

    ASSERT_DEATH ( {network_.RealPowerLoadAt ( static_cast<Types::vertexId>( 0 ) );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.RealPowerLoadAt ( static_cast<Types::vertexId>( 0 ) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , RealPowerLoadAt )
{ // Total real power load for a snapshot (here 0) for a vertexId
    Types::index snapshotId = 0;

    Types::real result = network_.RealPowerLoadAt( static_cast<Types::vertexId>( 3 ), snapshotId );
    EXPECT_EQ ( 8.0 , result );
    result = networkConst_.RealPowerLoadAt( static_cast<Types::vertexId>( 3 ), snapshotId );
    EXPECT_EQ ( 8.0 , result );
    result = network_.RealPowerLoadAt( static_cast<Types::vertexId>( 0 ), snapshotId );
    EXPECT_EQ ( 0 , result );
    result = networkConst_.RealPowerLoadAt( static_cast<Types::vertexId>( 0 ), snapshotId );
    EXPECT_EQ ( 0 , result );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , RealPowerLoadAt )
{ // Total real power load for a snapshot (here 0) for a vertexId
    Types::index snapshotId = 0;

    Types::real result = network_.RealPowerLoadAt( static_cast<Types::vertexId>( 3 ), snapshotId );
    EXPECT_EQ ( 5.0 , result );
    result = networkConst_.RealPowerLoadAt( static_cast<Types::vertexId>( 3 ), snapshotId );
    EXPECT_EQ ( 5.0 , result );
    result = network_.RealPowerLoadAt( static_cast<Types::vertexId>( 0 ), snapshotId );
    EXPECT_EQ ( 0 , result );
    result = networkConst_.RealPowerLoadAt( static_cast<Types::vertexId>( 0 ), snapshotId );
    EXPECT_EQ ( 0 , result );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark RealPowerLoadAtVertexObject
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , RealPowerLoadAtVertexObject )
{ // Total real power load for a snapshot (here 0 implicitly) for a vertexId
    auto assertionString = buildAssertionString ( "StaticGraph.hpp"
                                                , "StaticGraph"
                                                , "VertexAt"
                                                , "VertexExists\\(id\\)");

    ASSERT_DEATH ( {network_.RealPowerLoadAt ( network_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ) );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.RealPowerLoadAt ( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , RealPowerLoadAtVertexObject )
{ // Total real power load for a snapshot (here 0) for a vertexId
    Types::index snapshotId = 0;

    Types::real result = network_.RealPowerLoadAt( network_.Graph().VertexAt( static_cast<Types::vertexId>( 3 ) ), snapshotId );
    EXPECT_EQ ( 8.0 , result );
    result = networkConst_.RealPowerLoadAt( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 3 ) ), snapshotId );
    EXPECT_EQ ( 8.0 , result );
    result = network_.RealPowerLoadAt( network_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), snapshotId );
    EXPECT_EQ ( 0 , result );
    result = networkConst_.RealPowerLoadAt( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), snapshotId );
    EXPECT_EQ ( 0 , result );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , RealPowerLoadAtVertexObject )
{ // Total real power load for a snapshot (here 0) for a vertexId
    Types::index snapshotId = 0;

    Types::real result = network_.RealPowerLoadAt( network_.Graph().VertexAt( static_cast<Types::vertexId>( 3 ) ), snapshotId );
    EXPECT_EQ ( 5.0 , result );
    result = networkConst_.RealPowerLoadAt( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 3 ) ), snapshotId );
    EXPECT_EQ ( 5.0 , result );
    result = network_.RealPowerLoadAt( network_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), snapshotId );
    EXPECT_EQ ( 0 , result );
    result = networkConst_.RealPowerLoadAt( networkConst_.Graph().VertexAt( static_cast<Types::vertexId>( 0 ) ), snapshotId );
    EXPECT_EQ ( 0 , result );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark TotalRealPowerLoadBoundAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , TotalRealPowerLoadBoundAt )
{ // Total real power load for a snapshot (here 0 implicitly) for a vertexId
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TotalRealPowerLoadBoundAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.TotalRealPowerLoadBoundAt ( static_cast<Types::vertexId>( 0 ) );}
                 , assertionString );
    ASSERT_DEATH ( {networkConst_.TotalRealPowerLoadBoundAt ( static_cast<Types::vertexId>( 0 ) );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , TotalRealPowerLoadBoundAt )
{ // Total real power load for a snapshot (here 0) for a vertexId
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 ,               bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY , bound.Maximum() );
    bound = networkConst_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 ,               bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY , bound.Maximum() );

    network_.MakeExact ();
    bound = network_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 8.0 , bound.Minimum() );
    EXPECT_EQ ( 8.0 , bound.Maximum() );
    bound = networkConst_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 8.0 , bound.Minimum() );
    EXPECT_EQ ( 8.0 , bound.Maximum() );

    network_.MakeBounded ();
    bound = network_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 , bound.Minimum() );
    EXPECT_EQ ( 8.0 , bound.Maximum() );
    bound = networkConst_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 , bound.Minimum() );
    EXPECT_EQ ( 8.0 , bound.Maximum() );

    network_.MakeUnbounded ();
    bound = network_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 ,               bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY , bound.Maximum() );
    bound = networkConst_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 ,               bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY , bound.Maximum() );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , TotalRealPowerLoadBoundAt )
{ // Total real power load for a snapshot (here 0) for a vertexId
    network_.MakePureUnbounded ();
    TBound bound = network_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 ,               bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY , bound.Maximum() );
    bound = networkConst_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 ,               bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY , bound.Maximum() );

    network_.MakeExact ();
    bound = network_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 5.0 , bound.Minimum() );
    EXPECT_EQ ( 5.0 , bound.Maximum() );
    bound = networkConst_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 5.0 , bound.Minimum() );
    EXPECT_EQ ( 5.0 , bound.Maximum() );

    network_.MakeBounded ();
    bound = network_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 , bound.Minimum() );
    EXPECT_EQ ( 5.0 , bound.Maximum() );
    bound = networkConst_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 , bound.Minimum() );
    EXPECT_EQ ( 5.0 , bound.Maximum() );

    network_.MakeUnbounded ();
    bound = network_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 ,               bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY , bound.Maximum() );
    bound = networkConst_.TotalRealPowerLoadBoundAt( static_cast<Types::vertexId>( 3 ) );
    EXPECT_EQ ( 0.0 ,               bound.Minimum() );
    EXPECT_EQ ( Const::REAL_INFTY , bound.Maximum() );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark AddGeneratorRealPowerSnapshotAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , AddGeneratorRealPowerSnapshotAt )
{ // Add generator snapshot (real power)
    TGeneratorProperties generatorProperties;

    CreateExampleGeneratorProperties( generatorProperties );

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddGeneratorAt"
                                                , "Graph\\(\\).VertexExists\\( vertexId \\)");

    ASSERT_DEATH ( {network_.AddGeneratorAt(static_cast<Types::vertexId>(0), generatorProperties);}
                 , assertionString );

    Types::generatorId generatorId = static_cast<Types::generatorId>(0);
    assertionString = buildAssertionString ( "PowerGrid.hpp"
                                           , "PowerGrid"
                                           , "AddGeneratorRealPowerSnapshotAt"
                                           , "HasGenerator \\( generatorId \\)");
    ASSERT_DEATH ( {network_.AddGeneratorRealPowerSnapshotAt( generatorId, generatorProperties.RealPower() );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , AddGeneratorRealPowerSnapshotAt )
{ // Add generator snapshot (real power)
    TGeneratorProperties generatorProperties;

    CreateExampleGeneratorProperties( generatorProperties );
    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(2) ) );

    Types::generatorId generatorId = network_.AddGeneratorAt(static_cast<Types::vertexId>(2), generatorProperties);

    network_.AddGeneratorRealPowerSnapshotAt( generatorId, generatorProperties.RealPower() );
    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(2) ) );

    std::vector<TGeneratorProperties> generatorsAtVertex;
    network_.GeneratorsAt ( static_cast<Types::vertexId>(2), generatorsAtVertex );
    if ( !generatorsAtVertex.empty() )
    {
        generatorProperties = generatorsAtVertex[0];
    }
    EXPECT_EQ ( 1, generatorsAtVertex.size() );

    CheckExampleGeneratorProperties ( generatorProperties );
    generatorsAtVertex.clear();

    network_.GeneratorsAt ( static_cast<Types::vertexId>(2), generatorsAtVertex );
    if ( !generatorsAtVertex.empty() )
    {
        generatorProperties = generatorsAtVertex[0];
    }
    EXPECT_EQ ( 1, generatorsAtVertex.size() );
    CheckExampleGeneratorProperties ( generatorProperties );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , AddGeneratorRealPowerSnapshotAt )
{ // Add generator snapshot (real power)
    TGeneratorProperties generatorProperties;

    CreateExampleGeneratorProperties( generatorProperties );
    EXPECT_FALSE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );

    Types::generatorId generatorId = network_.AddGeneratorAt(static_cast<Types::vertexId>(1), generatorProperties);

    network_.AddGeneratorRealPowerSnapshotAt( generatorId, generatorProperties.RealPower() );
    network_.AddGeneratorRealPowerSnapshotAt( generatorId, generatorProperties.RealPower() );
    EXPECT_TRUE ( network_.HasGeneratorAt ( static_cast<Types::vertexId>(1) ) );

    std::vector<TGeneratorProperties> generatorsAtVertex;
    network_.GeneratorsAt ( static_cast<Types::vertexId>(1), generatorsAtVertex );
    if ( !generatorsAtVertex.empty() )
    {
        generatorProperties = generatorsAtVertex[0];
    }
    EXPECT_EQ ( 1, generatorsAtVertex.size() );

    CheckExampleGeneratorProperties ( generatorProperties );
    generatorsAtVertex.clear();

    network_.GeneratorsAt ( static_cast<Types::vertexId>(1), generatorsAtVertex );
    if ( !generatorsAtVertex.empty() )
    {
        generatorProperties = generatorsAtVertex[0];
    }
    EXPECT_EQ ( 1, generatorsAtVertex.size() );
    CheckExampleGeneratorProperties ( generatorProperties );

    EXPECT_EQ ( 9.9, network_.GeneratorRealPowerSnapshotAt(generatorId, 0) );
    EXPECT_EQ ( 9.9, network_.GeneratorRealPowerSnapshotAt(generatorId, 1) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark UpdateGeneratorSnapshotSize
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmpty
        , UpdateGeneratorSnapshotSize )
{
    network_.UpdateGeneratorSnapshotSize();
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , UpdateGeneratorSnapshotSize )
{
    network_.UpdateGeneratorSnapshotSize();
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , UpdateGeneratorSnapshotSize )
{
    network_.UpdateGeneratorSnapshotSize();
}

// ***********************************************************************
// ***********************************************************************
#pragma mark UpdateLoadSnapshotSize
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmpty
        , UpdateLoadSnapshotSize )
{
    network_.UpdateLoadSnapshotSize();
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , UpdateLoadSnapshotSize )
{
    network_.UpdateLoadSnapshotSize();
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , UpdateLoadSnapshotSize )
{
    network_.UpdateLoadSnapshotSize();
}

// ***********************************************************************
// ***********************************************************************
#pragma mark AddLoadSnapshotAt
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , AddLoadSnapshotAt )
{
    TLoadProperties loadProperties;

    CreateExampleLoadProperties( loadProperties );

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddLoadAt"
                                                , "Graph\\(\\).VertexExists \\( vertexId \\)");

    ASSERT_DEATH ( {network_.AddLoadAt(static_cast<Types::vertexId>(0), loadProperties);}
                 , assertionString );

    Types::loadId loadId = static_cast<Types::loadId>(0);
    assertionString = buildAssertionString ( "PowerGrid.hpp"
                                           , "PowerGrid"
                                           , "AddLoadSnapshotAt"
                                           , "HasLoad \\( loadId \\)");
    ASSERT_DEATH ( {network_.AddLoadSnapshotAt( loadId, loadProperties.RealPowerLoad() );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , AddLoadSnapshotAt )
{
    TLoadProperties loadProperties;

    CreateExampleLoadProperties( loadProperties );
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );

    Types::loadId loadId = network_.AddLoadAt(static_cast<Types::vertexId>(1), loadProperties);

    network_.AddLoadSnapshotAt( loadId, loadProperties.RealPowerLoad() );
    EXPECT_TRUE ( network_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );

    std::vector<TLoadProperties> loadsAtVertex;
    network_.LoadsAt ( static_cast<Types::vertexId>(1), loadsAtVertex );
    if ( !loadsAtVertex.empty() )
    {
        loadProperties = loadsAtVertex[0];
    }
    EXPECT_EQ ( 1, loadsAtVertex.size() );

    CheckExampleLoadProperties ( loadProperties );
    loadsAtVertex.clear();

    network_.LoadsAt ( static_cast<Types::vertexId>(1), loadsAtVertex );
    if ( !loadsAtVertex.empty() )
    {
        loadProperties = loadsAtVertex[0];
    }
    EXPECT_EQ ( 1, loadsAtVertex.size() );
    CheckExampleLoadProperties ( loadProperties );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , AddLoadSnapshotAt )
{
    TLoadProperties loadProperties;

    CreateExampleLoadProperties( loadProperties );
    EXPECT_FALSE ( network_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );

    Types::loadId loadId = network_.AddLoadAt(static_cast<Types::vertexId>(1), loadProperties);

    network_.AddLoadSnapshotAt( loadId, loadProperties.RealPowerLoad() );
    network_.AddLoadSnapshotAt( loadId, loadProperties.RealPowerLoad() );
    network_.AddLoadSnapshotAt( loadId, loadProperties.RealPowerLoad() );
    EXPECT_TRUE ( network_.HasLoadAt ( static_cast<Types::vertexId>(1) ) );

    std::vector<TLoadProperties> loadsAtVertex;
    network_.LoadsAt ( static_cast<Types::vertexId>(1), loadsAtVertex );
    if ( !loadsAtVertex.empty() )
    {
        loadProperties = loadsAtVertex[0];
    }
    EXPECT_EQ ( 1, loadsAtVertex.size() );

    CheckExampleLoadProperties ( loadProperties );
    loadsAtVertex.clear();

    network_.LoadsAt ( static_cast<Types::vertexId>(1), loadsAtVertex );
    if ( !loadsAtVertex.empty() )
    {
        loadProperties = loadsAtVertex[0];
    }
    EXPECT_EQ ( 1, loadsAtVertex.size() );
    CheckExampleLoadProperties ( loadProperties );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark AddSnapshotWeighting
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmpty
        , AddSnapshotWeighting )
{
    network_.AddSnapshotWeighting( 9.9 );

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddSnapshotWeighting"
                                                , "weight != Const::NONE");
    ASSERT_DEATH ( {network_.AddSnapshotWeighting( Const::NONE );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , AddSnapshotWeighting )
{
    network_.AddSnapshotWeighting( 9.9 );
    network_.AddSnapshotWeighting( 1.9 );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , AddSnapshotWeighting )
{
    network_.AddSnapshotWeighting( 4.9 );
    network_.AddSnapshotWeighting( 3.9 );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark AddSnapshotTimestamp
// ***********************************************************************
// ***********************************************************************

TEST_F  ( TestNetworkEmptyDeathTest
        , AddSnapshotTimestamp )
{
    network_.AddSnapshotTimestamp( "2019-09-19 19:19:19" );

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "AddSnapshotTimestamp"
                                                , "!timestamp.empty\\(\\)");
    ASSERT_DEATH ( {network_.AddSnapshotTimestamp( "" );}
                 , assertionString );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4a
        , AddSnapshotTimestamp )
{
    network_.AddSnapshotTimestamp( "2009-09-19 19:19:19" );
    network_.AddSnapshotTimestamp( "2019-09-19 19:19:19" );
}

TEST_F  ( TestPowerGridAcm2018MtsfFigure4b
        , AddSnapshotTimestamp )
{
    network_.AddSnapshotTimestamp( "2009-09-19 19:19:19" );
    network_.AddSnapshotTimestamp( "2019-09-19 19:19:19" );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark PositionOf
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , PositionOf )
{
    Types::index index = network_.PositionOf ( "2009-09-19 19:19:19" );
    EXPECT_EQ ( Const::NONE, index );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , PositionOf )
{
    Types::index index = network_.PositionOf ( "2009-09-19 19:19:19" );
    EXPECT_EQ ( Const::NONE, index );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4b
       , PositionOf )
{
    Types::index index = network_.PositionOf ( "2009-09-19 19:19:19" );
    EXPECT_EQ ( Const::NONE, index );
}

TEST_F ( TestPowerGridPyPsaExample
       , PositionOf )
{
    Types::index index = network_.PositionOf ( "2013-01-01 03:00:00" );
    EXPECT_EQ ( 3, index );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark TimestampAt
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , TimestampAt )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "TimestampAt"
                                                , "timestampPosition < timestamps_.size\\(\\)");
    ASSERT_DEATH ( {network_.TimestampAt ( 0 );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , TimestampAt )
{
    Types::timestampSnapshot timestamp = network_.TimestampAt ( 0 );
    EXPECT_EQ ( "0000-00-00 00:00:00", timestamp );
}

TEST_F ( TestPowerGridPyPsaExample
       , TimestampAt )
{
    Types::timestampSnapshot timestamp = network_.TimestampAt ( 7 );
    EXPECT_EQ ( "2013-01-01 07:00:00", timestamp );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorRealPowerSnapshotAtUsingGeneratorIdAndTimestamp
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmpty
       , GeneratorRealPowerSnapshotAtUsingGeneratorIdAndTimestamp )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "GeneratorRealPowerSnapshotAt"
                                                , "generatorId < NumberOfGenerators\\(\\)");

    ASSERT_DEATH ( {network_.GeneratorRealPowerSnapshotAt ( 0, "0000-00-00 00:00:00" );}
                 , assertionString );
}

TEST_F ( TestPowerGridPyPsaExample
       , GeneratorRealPowerSnapshotAtUsingGeneratorIdAndTimestamp )
{
    Types::generatorSnapshot snapshot = network_.GeneratorRealPowerSnapshotAt ( 1, "2013-01-01 03:00:00" );
    EXPECT_EQ ( 230, snapshot );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorRealPowerSnapshotAtUsingGeneratorAndTimestamp
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , GeneratorRealPowerSnapshotAtUsingGeneratorAndTimestamp )
{
    TGeneratorProperties generator = network_.GeneratorAt ( 0 );

    EXPECT_EQ ( Const::NONE
              , network_.GeneratorRealPowerSnapshotAt ( generator, "0000-00-00 01:00:00" ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , GeneratorRealPowerSnapshotAtUsingGeneratorAndTimestamp )
{
    TGeneratorProperties generator = network_.GeneratorAt ( 1 );
    EXPECT_EQ ( 230, network_.GeneratorRealPowerSnapshotAt ( generator, "2013-01-01 03:00:00" ) );
}

// ***********************************************************************
// ***********************************************************************
#pragma mark GeneratorRealPowerSnapshotsAt
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , GeneratorRealPowerSnapshotsAt )
{
    std::vector<Types::generatorSnapshot> snapshotsAtTimestamp;

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "GeneratorRealPowerSnapshotsAt"
                                                , "!timestamps_.empty\\(\\)");

    ASSERT_DEATH ( {network_.GeneratorRealPowerSnapshotsAt ( "0000-00-00 01:00:00"
                                                           , snapshotsAtTimestamp );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4aDeathTest
       , GeneratorRealPowerSnapshotsAt )
{
    std::vector<Types::generatorSnapshot> snapshotsAtTimestamp;
    snapshotsAtTimestamp.emplace_back ( Const::NONE );

    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "GeneratorRealPowerSnapshotsAt"
                                                , "snapshotsAtTimestamp.empty\\(\\)");

    ASSERT_DEATH ( {network_.GeneratorRealPowerSnapshotsAt ( "0000-00-00 01:00:00"
                                                           , snapshotsAtTimestamp );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , GeneratorRealPowerSnapshotsAt )
{
    std::vector<Types::generatorSnapshot> snapshotsAtTimestamp;

    network_.GeneratorRealPowerSnapshotsAt ( "0000-00-00 00:00:00"
                                           , snapshotsAtTimestamp );

    for ( auto snapshot : snapshotsAtTimestamp )
    {
        EXPECT_EQ ( 1.234, snapshot );
    }
}

// ***********************************************************************
// ***********************************************************************
#pragma mark ReactivePower
// ***********************************************************************
// ***********************************************************************
// @todo Not tested yet

// ***********************************************************************
// ***********************************************************************
#pragma mark LoadSnapshotLogic
// ***********************************************************************
// ***********************************************************************

TEST_F ( TestNetworkEmptyDeathTest
       , LoadSnapshotOfLoadsSize )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "LoadSnapshotOf"
                                                , "loadId < loads_.size\\(\\)");

    ASSERT_DEATH ( {network_.LoadSnapshotOf ( 10, 0 );}
                 , assertionString );
}

TEST_F ( TestNetworkEmptyDeathTest
       , LoadSnapshotOfConstNoneDeath )
{
    auto assertionString = buildAssertionString ( "PowerGrid.hpp"
                                                , "PowerGrid"
                                                , "LoadSnapshotOf"
                                                , "loadId != Const::NONE");

    ASSERT_DEATH ( {network_.LoadSnapshotOf ( Const::NONE, 0 );}
                 , assertionString );
}

TEST_F ( TestPowerGridAcm2018MtsfFigure4a
       , LoadSnapshotOf )
{
    EXPECT_EQ ( 8, network_.LoadSnapshotOf ( 0, 0 ) );
}

TEST_F ( TestPowerGridPyPsaExample
       , LoadSnapshotOf )
{
    EXPECT_EQ ( 137, network_.LoadSnapshotOf ( 7, 3 ) );
}

} // namespace egoa::test
