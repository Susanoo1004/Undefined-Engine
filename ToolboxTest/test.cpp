#include "pch.h"

#include <Toolbox/Matrix4x4.h>
#include <Toolbox/Matrix3x3.h>
#include <Toolbox/Matrix2x2.h>
#include <Toolbox/Quaternion.h>
#include <Toolbox/Vector4.h>
#include <Toolbox/Vector3.h>
#include <Toolbox/Vector2.h>
#include <Toolbox/calc.h>


#define PI 3.141592653589793f

#pragma region Vector2

TEST(Vector2, Unit) {
	EXPECT_EQ(Vector2::UnitX().x, 1);
	EXPECT_EQ(Vector2::UnitX().y, 0);

	EXPECT_EQ(Vector2::UnitY().x, 0);
	EXPECT_EQ(Vector2::UnitY().y, 1);
}

TEST(Vector2, Constructor) {
	EXPECT_EQ(Vector2(1, 2).x, 1);
	EXPECT_EQ(Vector2(1, 2).y, 2);

	EXPECT_EQ(Vector2(1).x, 1);
	EXPECT_EQ(Vector2(1).y, 1);

	EXPECT_EQ(Vector2({ 1,2 }).x, 1);
	EXPECT_EQ(Vector2({ 1,2 }).y, 2);

	EXPECT_FLOAT_EQ(Vector2(Vector2(1, 2), Vector2(1, 2)).x, 0);
	EXPECT_FLOAT_EQ(Vector2(Vector2(1, 2), Vector2(1, 2)).y, 0);

	EXPECT_FLOAT_EQ(Vector2(Vector2(1, 2), Vector2(0, 0)).x, -1);
	EXPECT_FLOAT_EQ(Vector2(Vector2(1, 2), Vector2(0, 0)).y, -2);

	EXPECT_FLOAT_EQ(Vector2(Vector2(0, 0), Vector2(1, 2)).x, 1);
	EXPECT_FLOAT_EQ(Vector2(Vector2(0, 0), Vector2(1, 2)).y, 2);
}

TEST(Vector2Function, Norm) {
	EXPECT_FLOAT_EQ(Vector2(4, 3).Norm(), 5.f);
	EXPECT_FLOAT_EQ(Vector2(0, 0).Norm(), 0);
	EXPECT_FLOAT_EQ(Vector2(-4, -3).Norm(), 5.f);

	EXPECT_FLOAT_EQ(Vector2(4, 3).SquaredNorm(), 25.f);
	EXPECT_FLOAT_EQ(Vector2(0, 0).SquaredNorm(), 0);
	EXPECT_FLOAT_EQ(Vector2(-4, -3).SquaredNorm(), 25.f);
}

TEST(Vector2Function, Normalized) {
	EXPECT_FLOAT_EQ(Vector2(0, 5).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector2(0, 5).Normalized().y, 1);

	EXPECT_FLOAT_EQ(Vector2(5, 0).Normalized().x, 1);
	EXPECT_FLOAT_EQ(Vector2(5, 0).Normalized().y, 0);

	EXPECT_FLOAT_EQ(Vector2(0, 0).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector2(0, 0).Normalized().y, 0);
}

TEST(Vector2Function, Normal) {
	EXPECT_FLOAT_EQ(Vector2(1, 0).Normal().x, 0);
	EXPECT_FLOAT_EQ(Vector2(1, 0).Normal().y, -1);
}

TEST(Vector2Function, DotProduct) {
	EXPECT_FLOAT_EQ(Vector2(1, 5).Dot({ 1, 3 }), 16);
	EXPECT_FLOAT_EQ(Vector2(-1, -5).Dot({ 1, 3 }), -16);
	EXPECT_FLOAT_EQ(Vector2(-1, -5).Dot({ -1, -3 }), 16);
	EXPECT_FLOAT_EQ(Vector2(0, 0).Dot({ 0, 0 }), 0);
}

TEST(Vector2Function, CrossProduct) {
	EXPECT_FLOAT_EQ(Vector2(14, 20).Cross({ 19, 42 }), 208);
	EXPECT_FLOAT_EQ(Vector2(14, 20).Determinant({ 19, 42 }), 208);
}


TEST(Vector2Function, Rotate) {
	EXPECT_FLOAT_EQ(Vector2(1, 0).Angle(), 0);
	EXPECT_FLOAT_EQ(Vector2(0, 1).Angle(), PI / 2);

	//rotate CounterClockWise
	EXPECT_NEAR(Vector2(1, 0).Rotate(PI / 2).x, 0, 0.0000001f);
	EXPECT_NEAR(Vector2(1, 0).Rotate(PI / 2).y, 1, 0.0000001f);

	EXPECT_NEAR(Vector2(1, 0).Rotate(PI / 2, Vector2(0, 0)).x, 0, 0.0000001f);
	EXPECT_NEAR(Vector2(1, 0).Rotate(PI / 2, Vector2(0, 0)).y, 1, 0.0000001f);

	EXPECT_FLOAT_EQ(Vector2(1, 0).Rotate(PI / 2, Vector2(-1, 0)).x, -1);
	EXPECT_NEAR(Vector2(1, 0).Rotate(PI / 2, Vector2(-1, 0)).y, 2, 0.0000001f);

	EXPECT_NEAR(Vector2(1, 0).Rotate(0, 1).x, 0, 0.0000001f);
	EXPECT_NEAR(Vector2(1, 0).Rotate(0, 1).y, 1, 0.0000001f);

	EXPECT_NEAR(Vector2(1, 0).Rotate(Vector2(-1, 0), 0, 1).x, -1, 0.0000001f);
	EXPECT_NEAR(Vector2(1, 0).Rotate(Vector2(-1, 0), 0, 1).y, 2, 0.0000001f);

	EXPECT_NEAR(Vector2::StatAngle(Vector2(1, 0), Vector2(0, 1)), PI / 2, 0.0000001f);
}

TEST(Vector2, operator) {
	EXPECT_EQ(Vector2(1, 2)[0], 1);
	EXPECT_EQ(Vector2(1, 2)[1], 2);

	EXPECT_FLOAT_EQ((Vector2(1, 2) + Vector2(1, 2)).x, 2);
	EXPECT_FLOAT_EQ((Vector2(1, 2) + Vector2(1, 2)).y, 4);

	EXPECT_FLOAT_EQ((Vector2(1, 2) - Vector2(1, 2)).x, 0);
	EXPECT_FLOAT_EQ((Vector2(1, 2) - Vector2(1, 2)).y, 0);

	EXPECT_FLOAT_EQ(-Vector2(1, 2).x, -1);
	EXPECT_FLOAT_EQ(-Vector2(1, 2).y, -2);

	EXPECT_FLOAT_EQ((Vector2(1, 2) * Vector2(1, 2)).x, 1);
	EXPECT_FLOAT_EQ((Vector2(1, 2) * Vector2(1, 2)).y, 4);

	EXPECT_FLOAT_EQ((Vector2(1, 2) * 4).x, 4);
	EXPECT_FLOAT_EQ((Vector2(1, 2) * 4).y, 8);

	EXPECT_FLOAT_EQ((Vector2(1, 2) / Vector2(1, 2)).x, 1);
	EXPECT_FLOAT_EQ((Vector2(1, 2) / Vector2(1, 2)).y, 1);

	EXPECT_FLOAT_EQ((Vector2(1, 2) / 2.f).x, 1.f / 2.f);
	EXPECT_FLOAT_EQ((Vector2(1, 2) / 2.f).y, 1.f);
}

TEST(Vector2, operatorEqual) {
	Vector2 test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test += Vector2(1, 2)).x, 2);
	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test += Vector2(1, 2)).y, 4);

	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test -= Vector2(1, 2)).x, 0);
	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test -= Vector2(1, 2)).y, 0);

	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test *= Vector2(1, 2)).x, 1);
	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test *= Vector2(1, 2)).y, 4);

	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test *= 4).x, 4);
	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test *= 4).y, 8);

	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test /= Vector2(1, 2)).x, 1);
	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test /= Vector2(1, 2)).y, 1);

	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test /= 2.f).x, 1.f / 2.f);
	test = Vector2(1, 2);
	EXPECT_FLOAT_EQ((test /= 2.f).y, 1.f);
}

TEST(Vector2, operatorComparison) {
	EXPECT_TRUE(Vector2(1, 2) == Vector2(1, 2));
	EXPECT_TRUE(!(Vector2(1, 2) == Vector2(1, 5)));

	EXPECT_TRUE(Vector2(1, 2) != Vector2(5, 2));
	EXPECT_TRUE(!(Vector2(1, 2) != Vector2(1, 2)));

	EXPECT_TRUE(Vector2(1, 2) < Vector2(2, 2));
	EXPECT_TRUE(!(Vector2(1, 2) < Vector2(1, 1)));

	EXPECT_TRUE(Vector2(2, 2) > Vector2(1, 2));
	EXPECT_TRUE(!(Vector2(1, 1) > Vector2(1, 2)));

	EXPECT_TRUE(Vector2(1, 2) <= Vector2(2, 2));
	EXPECT_TRUE(Vector2(2, 2) <= Vector2(2, 2));
	EXPECT_TRUE(!(Vector2(1, 2) <= Vector2(1, 1)));

	EXPECT_TRUE(Vector2(2, 2) >= Vector2(1, 2));
	EXPECT_TRUE(Vector2(2, 2) >= Vector2(2, 2));
	EXPECT_TRUE(!(Vector2(1, 1) >= Vector2(1, 2)));

}

#pragma endregion

#pragma region Vector3

TEST(Vector3, Unit) {
	EXPECT_EQ(Vector3::UnitX().x, 1);
	EXPECT_EQ(Vector3::UnitX().y, 0);
	EXPECT_EQ(Vector3::UnitX().z, 0);

	EXPECT_EQ(Vector3::UnitY().x, 0);
	EXPECT_EQ(Vector3::UnitY().y, 1);
	EXPECT_EQ(Vector3::UnitY().z, 0);

	EXPECT_EQ(Vector3::UnitZ().x, 0);
	EXPECT_EQ(Vector3::UnitZ().y, 0);
	EXPECT_EQ(Vector3::UnitZ().z, 1);
}

TEST(Vector3, Constructor) {
	EXPECT_EQ(Vector3(1, 2, 3).x, 1);
	EXPECT_EQ(Vector3(1, 2, 3).y, 2);
	EXPECT_EQ(Vector3(1, 2, 3).z, 3);

	EXPECT_EQ(Vector3(1).x, 1);
	EXPECT_EQ(Vector3(1).y, 1);
	EXPECT_EQ(Vector3(1).z, 1);

	EXPECT_EQ(Vector3({ 1,2,3 }).x, 1);
	EXPECT_EQ(Vector3({ 1,2,3 }).y, 2);
	EXPECT_EQ(Vector3({ 1,2,3 }).z, 3);

	EXPECT_FLOAT_EQ(Vector3(Vector3(1, 2, 3), Vector3(1, 2, 3)).x, 0);
	EXPECT_FLOAT_EQ(Vector3(Vector3(1, 2, 3), Vector3(1, 2, 3)).y, 0);
	EXPECT_FLOAT_EQ(Vector3(Vector3(1, 2, 3), Vector3(1, 2, 3)).z, 0);

	EXPECT_FLOAT_EQ(Vector3(Vector3(1, 2, 3), Vector3(0, 0, 0)).x, -1);
	EXPECT_FLOAT_EQ(Vector3(Vector3(1, 2, 3), Vector3(0, 0, 0)).y, -2);
	EXPECT_FLOAT_EQ(Vector3(Vector3(1, 2, 3), Vector3(0, 0, 0)).z, -3);

	EXPECT_FLOAT_EQ(Vector3(Vector3(0, 0, 0), Vector3(1, 2, 3)).x, 1);
	EXPECT_FLOAT_EQ(Vector3(Vector3(0, 0, 0), Vector3(1, 2, 3)).y, 2);
	EXPECT_FLOAT_EQ(Vector3(Vector3(0, 0, 0), Vector3(1, 2, 3)).z, 3);
}


TEST(Vector3Function, Norm) {
	EXPECT_FLOAT_EQ(Vector3(3, 4, 0).Norm(), 5);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 0).Norm(), 0);
	EXPECT_FLOAT_EQ(Vector3(0, -3, -4).Norm(), 5);

	EXPECT_FLOAT_EQ(Vector3(1, 1, 1).SquaredNorm(), 3);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 0).SquaredNorm(), 0);
	EXPECT_FLOAT_EQ(Vector3(-1, -1, -1).SquaredNorm(), 3);
}


TEST(Vector3Function, Normalized) {
	EXPECT_FLOAT_EQ(Vector3(0, 5, 0).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector3(0, 5, 0).Normalized().y, 1);
	EXPECT_FLOAT_EQ(Vector3(0, 5, 0).Normalized().z, 0);

	EXPECT_FLOAT_EQ(Vector3(5, 0, 0).Normalized().x, 1);
	EXPECT_FLOAT_EQ(Vector3(5, 0, 0).Normalized().y, 0);
	EXPECT_FLOAT_EQ(Vector3(5, 0, 0).Normalized().z, 0);

	EXPECT_FLOAT_EQ(Vector3(0, 0, 5).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 5).Normalized().y, 0);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 5).Normalized().z, 1);

	EXPECT_FLOAT_EQ(Vector3(0, 0, 0).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 0).Normalized().y, 0);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 0).Normalized().z, 0);
}

TEST(Vector3Function, DotProduct) {
	EXPECT_FLOAT_EQ(Vector3(1, 5, 3).Dot({ 1, 3, 3 }), 25);
	EXPECT_FLOAT_EQ(Vector3(-1, -5, -3).Dot({ 1, 3, 3 }), -25);
	EXPECT_FLOAT_EQ(Vector3(-1, -5, -3).Dot({ -1, -3, -3 }), 25);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 0).Dot({ 0, 0, 0 }), 0);
}

TEST(Vector3Function, StaticDotProduct) {
	EXPECT_FLOAT_EQ(Vector3::Dot(Vector3(1, 5, 3), Vector3(1, 3, 3)), 25);
	EXPECT_FLOAT_EQ(Vector3::Dot(Vector3(-1, -5, -3), Vector3(1, 3, 3)), -25);
	EXPECT_FLOAT_EQ(Vector3::Dot(Vector3(-1, -5, -3), Vector3(-1, -3, -3)), 25);
	EXPECT_FLOAT_EQ(Vector3::Dot(Vector3(0, 0, 0), Vector3(0, 0, 0)), 0);
}

TEST(Vector3Function, CrossProduct) {
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Cross(Vector3(0, 1, 0)).x, 0);
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Cross(Vector3(0, 1, 0)).y, 0);
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Cross(Vector3(0, 1, 0)).z, 1);

	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Cross(Vector3(0, 0, 1)).x, 0);
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Cross(Vector3(0, 0, 1)).y, -1);
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Cross(Vector3(0, 0, 1)).z, 0);

	EXPECT_FLOAT_EQ(Vector3(0, 0, 1).Cross(Vector3(0, 1, 0)).x, -1);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 1).Cross(Vector3(0, 1, 0)).y, 0);
	EXPECT_FLOAT_EQ(Vector3(0, 0, 1).Cross(Vector3(0, 1, 0)).z, 0);

	EXPECT_FLOAT_EQ(Vector3(0, 1, 0).Cross(Vector3(0, 1, 0)).x, 0);
	EXPECT_FLOAT_EQ(Vector3(0, 1, 0).Cross(Vector3(0, 1, 0)).y, 0);
	EXPECT_FLOAT_EQ(Vector3(0, 1, 0).Cross(Vector3(0, 1, 0)).z, 0);
}

TEST(Vector3Function, StaticCrossProduct) {
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(1, 0, 0), (Vector3(0, 1, 0))).x, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(1, 0, 0), (Vector3(0, 1, 0))).y, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(1, 0, 0), (Vector3(0, 1, 0))).z, 1);

	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(1, 0, 0), (Vector3(0, 0, 1))).x, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(1, 0, 0), (Vector3(0, 0, 1))).y, -1);
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(1, 0, 0), (Vector3(0, 0, 1))).z, 0);

	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(0, 0, 1), (Vector3(0, 1, 0))).x, -1);
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(0, 0, 1), (Vector3(0, 1, 0))).y, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(0, 0, 1), (Vector3(0, 1, 0))).z, 0);

	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(0, 1, 0), (Vector3(0, 1, 0))).x, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(0, 1, 0), (Vector3(0, 1, 0))).y, 0);
	EXPECT_FLOAT_EQ(Vector3::Cross(Vector3(0, 1, 0), (Vector3(0, 1, 0))).z, 0);
}

TEST(Vector3Function, Angle) {
	EXPECT_FLOAT_EQ(Vector3::Angle(Vector3(1, 0, 0), Vector3(1, 0, 0)), 0.f);
	EXPECT_FLOAT_EQ(Vector3::Angle(Vector3(1, 0, 0), Vector3(0, 1, 0)), PI / 2.f);
	EXPECT_FLOAT_EQ(Vector3::Angle(Vector3(1, 0, 0), Vector3(0, 0, 1)), PI / 2.f);
	EXPECT_FLOAT_EQ(Vector3::Angle(Vector3(1, 0, 0), Vector3(0, -1, 0)), PI / 2.f);
	EXPECT_FLOAT_EQ(Vector3::Angle(Vector3(1, 0, 0), Vector3(-1, 0, 0)), PI);
	EXPECT_FLOAT_EQ(Vector3::Angle(Vector3(1, 0, 0), Vector3(0, 1, 1)), PI / 2.f);
}

TEST(Vector3Function, Rotate) {
	EXPECT_TRUE(false);
	/*
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Rotate(0, Vector3(0, 0, 1)).x, 1);
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Rotate(0, Vector3(0, 0, 1)).y, 0);
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Rotate(0, Vector3(0, 0, 1)).z, 0);

	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Rotate(PI / 2.f, Vector3(0, 0, 1)).x, 0);
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Rotate(PI / 2.f, Vector3(0, 0, 1)).y, 1);
	EXPECT_FLOAT_EQ(Vector3(1, 0, 0).Rotate(PI / 2.f, Vector3(0, 0, 1)).z, 0);
	*/
}

TEST(Vector3, operator) {
	EXPECT_EQ(Vector3(1, 2, 3)[0], 1);
	EXPECT_EQ(Vector3(1, 2, 3)[1], 2);
	EXPECT_EQ(Vector3(1, 2, 3)[2], 3);

	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) + Vector3(1, 2, 3)).x, 2);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) + Vector3(1, 2, 3)).y, 4);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) + Vector3(1, 2, 3)).z, 6);

	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) - Vector3(1, 2, 3)).x, 0);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) - Vector3(1, 2, 3)).y, 0);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) - Vector3(1, 2, 3)).z, 0);

	EXPECT_FLOAT_EQ(-Vector3(1, 2, 3).x, -1);
	EXPECT_FLOAT_EQ(-Vector3(1, 2, 3).y, -2);
	EXPECT_FLOAT_EQ(-Vector3(1, 2, 3).z, -3);

	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) * Vector3(1, 2, 3)).x, 1);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) * Vector3(1, 2, 3)).y, 4);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) * Vector3(1, 2, 3)).z, 9);

	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) * 4).x, 4);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) * 4).y, 8);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) * 4).z, 12);

	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) / Vector3(1, 2, 3)).x, 1);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) / Vector3(1, 2, 3)).y, 1);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) / Vector3(1, 2, 3)).z, 1);

	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) / 2.f).x, 1.f / 2.f);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) / 2.f).y, 1.f);
	EXPECT_FLOAT_EQ((Vector3(1, 2, 3) / 2.f).z, 3.f / 2.f);
}


TEST(Vector3, operatorEqual) {
	Vector3 test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test += Vector3(1, 2, 3)).x, 2);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test += Vector3(1, 2, 3)).y, 4);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test += Vector3(1, 2, 3)).z, 6);
	test = Vector3(1, 2, 3);

	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test -= Vector3(1, 2, 3)).x, 0);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test -= Vector3(1, 2, 3)).y, 0);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test -= Vector3(1, 2, 3)).z, 0);
	test = Vector3(1, 2, 3);

	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test *= Vector3(1, 2, 3)).x, 1);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test *= Vector3(1, 2, 3)).y, 4);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test *= Vector3(1, 2, 3)).z, 9);
	test = Vector3(1, 2, 3);

	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test *= 4).x, 4);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test *= 4).y, 8);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test *= 4).z, 12);
	test = Vector3(1, 2, 3);

	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test /= Vector3(1, 2, 3)).x, 1);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test /= Vector3(1, 2, 3)).y, 1);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test /= Vector3(1, 2, 3)).z, 1);

	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test /= 2.f).x, 1.f / 2.f);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test /= 2.f).y, 1.f);
	test = Vector3(1, 2, 3);
	EXPECT_FLOAT_EQ((test /= 2.f).z, 3.f / 2.f);
}


TEST(Vector3, operatorComparison) {
	EXPECT_TRUE(Vector3(1, 2, 3) == Vector3(1, 2, 3));
	EXPECT_TRUE(!(Vector3(1, 2, 3) == Vector3(1, 5, 3)));

	EXPECT_TRUE(Vector3(1, 2, 3) != Vector3(5, 2, 3));
	EXPECT_TRUE(!(Vector3(1, 2, 3) != Vector3(1, 2, 3)));

	EXPECT_TRUE(Vector3(1, 2, 3) < Vector3(2, 2, 3));
	EXPECT_TRUE(!(Vector3(1, 2, 3) < Vector3(1, 1, 1)));

	EXPECT_TRUE(Vector3(2, 2, 3) > Vector3(1, 2, 3));
	EXPECT_TRUE(!(Vector3(1, 1, 1) > Vector3(1, 2, 3)));

	EXPECT_TRUE(Vector3(1, 2, 3) <= Vector3(2, 2, 3));
	EXPECT_TRUE(Vector3(2, 2, 3) <= Vector3(2, 2, 3));
	EXPECT_TRUE(!(Vector3(1, 2, 3) <= Vector3(1, 1, 1)));

	EXPECT_TRUE(Vector3(2, 2, 3) >= Vector3(1, 2, 3));
	EXPECT_TRUE(Vector3(2, 2, 3) >= Vector3(2, 2, 3));
	EXPECT_TRUE(!(Vector3(1, 1, 1) >= Vector3(1, 2, 3)));
}


#pragma endregion

#pragma region Vector4

TEST(Vector4, Unit) {
	EXPECT_EQ(Vector4::UnitX().x, 1);
	EXPECT_EQ(Vector4::UnitX().y, 0);
	EXPECT_EQ(Vector4::UnitX().z, 0);
	EXPECT_EQ(Vector4::UnitX().w, 0);

	EXPECT_EQ(Vector4::UnitY().x, 0);
	EXPECT_EQ(Vector4::UnitY().y, 1);
	EXPECT_EQ(Vector4::UnitY().z, 0);
	EXPECT_EQ(Vector4::UnitY().w, 0);

	EXPECT_EQ(Vector4::UnitZ().x, 0);
	EXPECT_EQ(Vector4::UnitZ().y, 0);
	EXPECT_EQ(Vector4::UnitZ().z, 1);
	EXPECT_EQ(Vector4::UnitZ().w, 0);

	EXPECT_EQ(Vector4::UnitW().x, 0);
	EXPECT_EQ(Vector4::UnitW().y, 0);
	EXPECT_EQ(Vector4::UnitW().z, 0);
	EXPECT_EQ(Vector4::UnitW().w, 1);
}

TEST(Vector4, Constructor) {
	EXPECT_EQ(Vector4(1, 2, 3, 4).x, 1);
	EXPECT_EQ(Vector4(1, 2, 3, 4).y, 2);
	EXPECT_EQ(Vector4(1, 2, 3, 4).z, 3);
	EXPECT_EQ(Vector4(1, 2, 3, 4).w, 4);

	EXPECT_EQ(Vector4(1).x, 1);
	EXPECT_EQ(Vector4(1).y, 1);
	EXPECT_EQ(Vector4(1).z, 1);
	EXPECT_EQ(Vector4(1).w, 1);

	EXPECT_EQ(Vector4({ 1,2,3,4 }).x, 1);
	EXPECT_EQ(Vector4({ 1,2,3,4 }).y, 2);
	EXPECT_EQ(Vector4({ 1,2,3,4 }).z, 3);
	EXPECT_EQ(Vector4({ 1,2,3,4 }).w, 4);

	EXPECT_FLOAT_EQ(Vector4(Vector4(1, 2, 3, 4), Vector4(1, 2, 3, 4)).x, 0);
	EXPECT_FLOAT_EQ(Vector4(Vector4(1, 2, 3, 4), Vector4(1, 2, 3, 4)).y, 0);
	EXPECT_FLOAT_EQ(Vector4(Vector4(1, 2, 3, 4), Vector4(1, 2, 3, 4)).z, 0);
	EXPECT_FLOAT_EQ(Vector4(Vector4(1, 2, 3, 4), Vector4(1, 2, 3, 4)).w, 0);

	EXPECT_FLOAT_EQ(Vector4(Vector4(1, 2, 3, 4), Vector4(0, 0, 0, 0)).x, -1);
	EXPECT_FLOAT_EQ(Vector4(Vector4(1, 2, 3, 4), Vector4(0, 0, 0, 0)).y, -2);
	EXPECT_FLOAT_EQ(Vector4(Vector4(1, 2, 3, 4), Vector4(0, 0, 0, 0)).z, -3);
	EXPECT_FLOAT_EQ(Vector4(Vector4(1, 2, 3, 4), Vector4(0, 0, 0, 0)).w, -4);

	EXPECT_FLOAT_EQ(Vector4(Vector4(0, 0, 0, 0), Vector4(1, 2, 3, 4)).x, 1);
	EXPECT_FLOAT_EQ(Vector4(Vector4(0, 0, 0, 0), Vector4(1, 2, 3, 4)).y, 2);
	EXPECT_FLOAT_EQ(Vector4(Vector4(0, 0, 0, 0), Vector4(1, 2, 3, 4)).z, 3);
	EXPECT_FLOAT_EQ(Vector4(Vector4(0, 0, 0, 0), Vector4(1, 2, 3, 4)).w, 4);
}

TEST(Vector4Function, Norm) {
	EXPECT_FLOAT_EQ(Vector4(1, 1, 1, 1).Norm(), 2);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 0).Norm(), 0);
	EXPECT_FLOAT_EQ(Vector4(-1, -1, -1, -1).Norm(), 2);

	EXPECT_FLOAT_EQ(Vector4(1, 1, 1, 1).SquaredNorm(), 4);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 0).SquaredNorm(), 0);
	EXPECT_FLOAT_EQ(Vector4(-1, -1, -1, -1).SquaredNorm(), 4);
}

TEST(Vector4Function, Normalized) {
	EXPECT_FLOAT_EQ(Vector4(0, 5, 0, 0).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 5, 0, 0).Normalized().y, 1);
	EXPECT_FLOAT_EQ(Vector4(0, 5, 0, 0).Normalized().z, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 5, 0, 0).Normalized().w, 0);

	EXPECT_FLOAT_EQ(Vector4(5, 0, 0, 0).Normalized().x, 1);
	EXPECT_FLOAT_EQ(Vector4(5, 0, 0, 0).Normalized().y, 0);
	EXPECT_FLOAT_EQ(Vector4(5, 0, 0, 0).Normalized().z, 0);
	EXPECT_FLOAT_EQ(Vector4(5, 0, 0, 0).Normalized().w, 0);

	EXPECT_FLOAT_EQ(Vector4(0, 0, 5, 0).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 5, 0).Normalized().y, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 5, 0).Normalized().z, 1);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 5, 0).Normalized().w, 0);

	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 5).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 5).Normalized().y, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 5).Normalized().z, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 5).Normalized().w, 1);

	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 0).Normalized().x, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 0).Normalized().y, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 0).Normalized().z, 0);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 0).Normalized().w, 0);
}

TEST(Vector4Function, DotProduct) {
	EXPECT_FLOAT_EQ(Vector4(1, 5, 3, 0).Dot({ 1, 3, 3, 0 }), 25);
	EXPECT_FLOAT_EQ(Vector4(-1, -5, -3, 0).Dot({ 1, 3, 3, 0 }), -25);
	EXPECT_FLOAT_EQ(Vector4(-1, -5, -3, 0).Dot({ -1, -3, -3, 0 }), 25);
	EXPECT_FLOAT_EQ(Vector4(0, 0, 0, 0).Dot({ 0, 0, 0, 0 }), 0);
}

TEST(Vector4, operator) {
	EXPECT_EQ(Vector4(1, 2, 3, 4)[0], 1);
	EXPECT_EQ(Vector4(1, 2, 3, 4)[1], 2);
	EXPECT_EQ(Vector4(1, 2, 3, 4)[2], 3);
	EXPECT_EQ(Vector4(1, 2, 3, 4)[3], 4);

	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) + Vector4(1, 2, 3, 4)).x, 2);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) + Vector4(1, 2, 3, 4)).y, 4);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) + Vector4(1, 2, 3, 4)).z, 6);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) + Vector4(1, 2, 3, 4)).w, 8);

	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) - Vector4(1, 2, 3, 4)).x, 0);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) - Vector4(1, 2, 3, 4)).y, 0);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) - Vector4(1, 2, 3, 4)).z, 0);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) - Vector4(1, 2, 3, 4)).w, 0);

	EXPECT_FLOAT_EQ(-Vector4(1, 2, 3, 4).x, -1);
	EXPECT_FLOAT_EQ(-Vector4(1, 2, 3, 4).y, -2);
	EXPECT_FLOAT_EQ(-Vector4(1, 2, 3, 4).z, -3);
	EXPECT_FLOAT_EQ(-Vector4(1, 2, 3, 4).w, -4);

	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) * Vector4(1, 2, 3, 4)).x, 1);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) * Vector4(1, 2, 3, 4)).y, 4);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) * Vector4(1, 2, 3, 4)).z, 9);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) * Vector4(1, 2, 3, 4)).w, 16);

	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) * 4).x, 4);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) * 4).y, 8);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) * 4).z, 12);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) * 4).w, 16);

	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) / Vector4(1, 2, 3, 4)).x, 1);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) / Vector4(1, 2, 3, 4)).y, 1);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) / Vector4(1, 2, 3, 4)).z, 1);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) / Vector4(1, 2, 3, 4)).w, 1);

	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) / 2.f).x, 1.f / 2.f);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) / 2.f).y, 1.f);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) / 2.f).z, 3.f / 2.f);
	EXPECT_FLOAT_EQ((Vector4(1, 2, 3, 4) / 2.f).w, 2.f);
}

TEST(Vector4, operatorEqual) {
	Vector4 test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test += Vector4(1, 2, 3, 4)).x, 2);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test += Vector4(1, 2, 3, 4)).y, 4);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test += Vector4(1, 2, 3, 4)).z, 6);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test += Vector4(1, 2, 3, 4)).w, 8);

	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test -= Vector4(1, 2, 3, 4)).x, 0);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test -= Vector4(1, 2, 3, 4)).y, 0);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test -= Vector4(1, 2, 3, 4)).z, 0);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test -= Vector4(1, 2, 3, 4)).w, 0);

	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= Vector4(1, 2, 3, 4)).x, 1);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= Vector4(1, 2, 3, 4)).y, 4);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= Vector4(1, 2, 3, 4)).z, 9);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= Vector4(1, 2, 3, 4)).w, 16);

	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= 4).x, 4);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= 4).y, 8);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= 4).z, 12);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= 4).w, 16);

	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= Vector4(1, 2, 3, 4)).x, 1);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= Vector4(1, 2, 3, 4)).y, 1);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= Vector4(1, 2, 3, 4)).z, 1);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= Vector4(1, 2, 3, 4)).w, 1);

	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= 2.f).x, 1.f / 2.f);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= 2.f).y, 1.f);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= 2.f).z, 3.f / 2.f);
	test = Vector4(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= 2.f).w, 2.f);
}

TEST(Vector4, operatorComparison) {
	EXPECT_TRUE(Vector4(1, 2, 3, 4) == Vector4(1, 2, 3, 4));
	EXPECT_TRUE(!(Vector4(1, 2, 3, 4) == Vector4(1, 5, 3, 4)));

	EXPECT_TRUE(Vector4(1, 2, 3, 4) != Vector4(5, 2, 3, 4));
	EXPECT_TRUE(!(Vector4(1, 2, 3, 4) != Vector4(1, 2, 3, 4)));

	EXPECT_TRUE(Vector4(1, 2, 3, 4) < Vector4(2, 2, 3, 4));
	EXPECT_TRUE(!(Vector4(1, 2, 3, 4) < Vector4(1, 1, 1, 1)));

	EXPECT_TRUE(Vector4(2, 2, 3, 4) > Vector4(1, 2, 3, 4));
	EXPECT_TRUE(!(Vector4(1, 1, 1, 1) > Vector4(1, 2, 3, 4)));

	EXPECT_TRUE(Vector4(1, 2, 3, 4) <= Vector4(2, 2, 3, 4));
	EXPECT_TRUE(Vector4(2, 2, 3, 4) <= Vector4(2, 2, 3, 4));
	EXPECT_TRUE(!(Vector4(1, 2, 3, 4) <= Vector4(1, 1, 1, 1)));

	EXPECT_TRUE(Vector4(2, 2, 3, 4) >= Vector4(1, 2, 3, 4));
	EXPECT_TRUE(Vector4(2, 2, 3, 4) >= Vector4(2, 2, 3, 4));
	EXPECT_TRUE(!(Vector4(1, 1, 1, 1) >= Vector4(1, 2, 3, 4)));
}

#pragma endregion

#pragma region Quaternion

TEST(Quaternion, Constructor) {
	EXPECT_EQ(Quaternion(1, 2, 3, 4).imaginary.x, 1);
	EXPECT_EQ(Quaternion(1, 2, 3, 4).imaginary.y, 2);
	EXPECT_EQ(Quaternion(1, 2, 3, 4).imaginary.z, 3);
	EXPECT_EQ(Quaternion(1, 2, 3, 4).real, 4);

	EXPECT_EQ(Quaternion(1).imaginary.x, 1);
	EXPECT_EQ(Quaternion(1).imaginary.y, 1);
	EXPECT_EQ(Quaternion(1).imaginary.z, 1);
	EXPECT_EQ(Quaternion(1).real, 1);

	EXPECT_EQ(Quaternion(Vector3(1, 2, 3), 4).imaginary.x, 1);
	EXPECT_EQ(Quaternion(Vector3(1, 2, 3), 4).imaginary.y, 2);
	EXPECT_EQ(Quaternion(Vector3(1, 2, 3), 4).imaginary.z, 3);
	EXPECT_EQ(Quaternion(Vector3(1, 2, 3), 4).real, 4);

	EXPECT_EQ(Quaternion({ 1,2,3,4 }).imaginary.x, 1);
	EXPECT_EQ(Quaternion({ 1,2,3,4 }).imaginary.y, 2);
	EXPECT_EQ(Quaternion({ 1,2,3,4 }).imaginary.z, 3);
	EXPECT_EQ(Quaternion({ 1,2,3,4 }).real, 4);
}

TEST(QuaternionFunction, Norm) {
	EXPECT_FLOAT_EQ(Quaternion(1, 1, 1, 1).Norm(), 2);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Norm(), 0);
	EXPECT_FLOAT_EQ(Quaternion(-1, -1, -1, -1).Norm(), 2);

	EXPECT_FLOAT_EQ(Quaternion(1, 1, 1, 1).SquaredNorm(), 4);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).SquaredNorm(), 0);
	EXPECT_FLOAT_EQ(Quaternion(-1, -1, -1, -1).SquaredNorm(), 4);
}

TEST(QuaternionFunction, Conjugate) {
	EXPECT_FLOAT_EQ(Quaternion(1, 2, 3, 5).Conjugate().imaginary.x, -1);
	EXPECT_FLOAT_EQ(Quaternion(1, 2, 3, 5).Conjugate().imaginary.y, -2);
	EXPECT_FLOAT_EQ(Quaternion(1, 2, 3, 5).Conjugate().imaginary.z, -3);
	EXPECT_FLOAT_EQ(Quaternion(1, 2, 3, 5).Conjugate().real, 5);
}

TEST(QuaternionFunction, Normalized) {
	EXPECT_FLOAT_EQ(Quaternion(0, 5, 0, 0).Normalized().imaginary.x, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 5, 0, 0).Normalized().imaginary.y, 1);
	EXPECT_FLOAT_EQ(Quaternion(0, 5, 0, 0).Normalized().imaginary.z, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 5, 0, 0).Normalized().real, 0);

	EXPECT_FLOAT_EQ(Quaternion(5, 0, 0, 0).Normalized().imaginary.x, 1);
	EXPECT_FLOAT_EQ(Quaternion(5, 0, 0, 0).Normalized().imaginary.y, 0);
	EXPECT_FLOAT_EQ(Quaternion(5, 0, 0, 0).Normalized().imaginary.z, 0);
	EXPECT_FLOAT_EQ(Quaternion(5, 0, 0, 0).Normalized().real, 0);

	EXPECT_FLOAT_EQ(Quaternion(0, 0, 5, 0).Normalized().imaginary.x, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 5, 0).Normalized().imaginary.y, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 5, 0).Normalized().imaginary.z, 1);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 5, 0).Normalized().real, 0);

	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 5).Normalized().imaginary.x, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 5).Normalized().imaginary.y, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 5).Normalized().imaginary.z, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 5).Normalized().real, 1);

	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Normalized().imaginary.x, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Normalized().imaginary.y, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Normalized().imaginary.z, 0);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Normalized().real, 0);
}

TEST(QuaternionFunction, DotProduct) {
	EXPECT_FLOAT_EQ(Quaternion(1, 5, 3, 0).Dot({ 1, 3, 3, 0 }), 25);
	EXPECT_FLOAT_EQ(Quaternion(-1, -5, -3, 0).Dot({ 1, 3, 3, 0 }), -25);
	EXPECT_FLOAT_EQ(Quaternion(-1, -5, -3, 0).Dot({ -1, -3, -3, 0 }), 25);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Dot({ 0, 0, 0, 0 }), 0);
}

TEST(QuaternionFunction, Inverse) {
	EXPECT_FLOAT_EQ(Quaternion(0, 1, 0, 1).Inverse().imaginary.x, 0.f);
	EXPECT_FLOAT_EQ(Quaternion(0, 1, 0, 1).Inverse().imaginary.y, -0.5f);
	EXPECT_FLOAT_EQ(Quaternion(0, 1, 0, 1).Inverse().imaginary.z, 0.f);
	EXPECT_FLOAT_EQ(Quaternion(0, 1, 0, 1).Inverse().real, 0.5f);
	/*
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Inverse().imaginary.x, 0.f);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Inverse().imaginary.y, 0.f);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Inverse().imaginary.z, 0.f);
	EXPECT_FLOAT_EQ(Quaternion(0, 0, 0, 0).Inverse().real, 0.f);
	*/
}

TEST(QuaternionFunction, GetRQ) {
	Vector3 axis = Vector3(1, 0, 0);
	float rot = 0;
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.x, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.y, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.z, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).real, 1.f);

	axis = Vector3(0, 1, 0);
	rot = PI / 2.f;
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.x, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.y, 0.70710677f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.z, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).real, 0.70710677f);

	axis = Vector3(0, 1, 0);
	rot = PI;
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.x, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.y, 1.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.z, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).real, 0.f);

	axis = Vector3(0, 1, 0);
	rot = -PI / 2.f;
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.x, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.y, -0.70710677f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.z, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).real, 0.70710677f);

	axis = Vector3(1, 0, 0);
	rot = PI / 2.f;
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.x, 0.70710677f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.y, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).imaginary.z, 0.f);
	EXPECT_FLOAT_EQ(Quaternion::GetRQ(axis, rot).real, 0.70710677f);
}

TEST(QuaternionFunction, ToMatrix) {

}

TEST(QuaternionFunction, Rotate) {

}

TEST(QuaternionFunction, ToRotationMatrix) {

}

TEST(QuaternionFunction, SLerp) {

}

TEST(Quaternion, operator) {
	/*
	EXPECT_EQ(Quaternion(1, 2, 3, 4)[0], 1);
	EXPECT_EQ(Quaternion(1, 2, 3, 4)[1], 2);
	EXPECT_EQ(Quaternion(1, 2, 3, 4)[2], 3);
	EXPECT_EQ(Quaternion(1, 2, 3, 4)[3], 4);
	*/

	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) + Quaternion(1, 2, 3, 4)).imaginary.x, 2);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) + Quaternion(1, 2, 3, 4)).imaginary.y, 4);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) + Quaternion(1, 2, 3, 4)).imaginary.z, 6);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) + Quaternion(1, 2, 3, 4)).real, 8);

	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) - Quaternion(1, 2, 3, 4)).imaginary.x, 0);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) - Quaternion(1, 2, 3, 4)).imaginary.y, 0);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) - Quaternion(1, 2, 3, 4)).imaginary.z, 0);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) - Quaternion(1, 2, 3, 4)).real, 0);

	EXPECT_FLOAT_EQ(-Quaternion(1, 2, 3, 4).imaginary.x, -1);
	EXPECT_FLOAT_EQ(-Quaternion(1, 2, 3, 4).imaginary.y, -2);
	EXPECT_FLOAT_EQ(-Quaternion(1, 2, 3, 4).imaginary.z, -3);
	EXPECT_FLOAT_EQ(-Quaternion(1, 2, 3, 4).real, -4);

	// TODO: actual Math instead of copy-paste
	/*
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) * Quaternion(1, 2, 3, 4)).imaginary.x, 1);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) * Quaternion(1, 2, 3, 4)).imaginary.y, 4);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) * Quaternion(1, 2, 3, 4)).imaginary.z, 9);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) * Quaternion(1, 2, 3, 4)).real, 16);

	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) * 4).imaginary.x, 4);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) * 4).imaginary.y, 8);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) * 4).imaginary.z, 12);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) * 4).real, 16);

	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) / Quaternion(1, 2, 3, 4)).imaginary.x, 1);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) / Quaternion(1, 2, 3, 4)).imaginary.y, 1);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) / Quaternion(1, 2, 3, 4)).imaginary.z, 1);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) / Quaternion(1, 2, 3, 4)).real, 1);

	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) / 2.f).imaginary.x, 1.f / 2.f);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) / 2.f).imaginary.y, 1.f);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) / 2.f).imaginary.z, 3.f / 2.f);
	EXPECT_FLOAT_EQ((Quaternion(1, 2, 3, 4) / 2.f).real, 2.f);
	*/
}

TEST(Quaternion, operatorEqual) {
	Quaternion test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test += Quaternion(1, 2, 3, 4)).imaginary.x, 2);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test += Quaternion(1, 2, 3, 4)).imaginary.y, 4);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test += Quaternion(1, 2, 3, 4)).imaginary.z, 6);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test += Quaternion(1, 2, 3, 4)).real, 8);

	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test -= Quaternion(1, 2, 3, 4)).imaginary.x, 0);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test -= Quaternion(1, 2, 3, 4)).imaginary.y, 0);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test -= Quaternion(1, 2, 3, 4)).imaginary.z, 0);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test -= Quaternion(1, 2, 3, 4)).real, 0);

	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= Quaternion(1, 2, 3, 4)).imaginary.x, 1);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= Quaternion(1, 2, 3, 4)).imaginary.y, 4);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= Quaternion(1, 2, 3, 4)).imaginary.z, 9);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= Quaternion(1, 2, 3, 4)).real, 16);

	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= 4).imaginary.x, 4);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= 4).imaginary.y, 8);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= 4).imaginary.z, 12);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test *= 4).real, 16);

	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= Quaternion(1, 2, 3, 4)).imaginary.x, 1);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= Quaternion(1, 2, 3, 4)).imaginary.y, 1);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= Quaternion(1, 2, 3, 4)).imaginary.z, 1);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= Quaternion(1, 2, 3, 4)).real, 1);

	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= 2.f).imaginary.x, 1.f / 2.f);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= 2.f).imaginary.y, 1.f);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= 2.f).imaginary.z, 3.f / 2.f);
	test = Quaternion(1, 2, 3, 4);
	EXPECT_FLOAT_EQ((test /= 2.f).real, 2.f);
}

#pragma endregion

#pragma region Matrix2x2

TEST(Matrix2x2, constructor) {
	Matrix2x2 testMat = Matrix2x2();
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			EXPECT_EQ(testMat[i][j], 0);

	testMat = Matrix2x2(5);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			EXPECT_EQ(testMat[i][j], 5);

	testMat = Matrix2x2(Vector2(1, 2), Vector2(3, 4));
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			EXPECT_EQ(testMat[i][j], i * 2 + j + 1);

	testMat = Matrix2x2(
		1, 2,
		3, 4
	);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			EXPECT_EQ(testMat[i][j], i * 2 + j + 1);

	Matrix2x2 testCopy(testMat);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			EXPECT_EQ(testCopy[i][j], testMat[i][j]);

	testMat = Matrix2x2::Identity();
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			EXPECT_EQ(testMat[i][j], i == j ? 1 : 0);
}

TEST(Matrix2x2Function, isDiagonal) {
	EXPECT_TRUE(Matrix2x2().IsDiagonal());
	EXPECT_FALSE(Matrix2x2(5).IsDiagonal());
	Matrix2x2 testMat = Matrix2x2(
		1, 0,
		0, 5
	);
	EXPECT_TRUE(testMat.IsDiagonal());
}

TEST(Matrix2x2Function, isIdentity) {
	Matrix2x2 testMat = Matrix2x2(
		1, 0, 
		0, 1
	);
	EXPECT_TRUE(testMat.IsIdentity());
	EXPECT_TRUE(Matrix2x2::Identity().IsIdentity());
	EXPECT_FALSE(Matrix2x2().IsIdentity());
	EXPECT_FALSE(Matrix2x2(5).IsIdentity());
	testMat = Matrix2x2(
		1, 0,
		0, 5
	);
	EXPECT_FALSE(testMat.IsIdentity());
}

TEST(Matrix2x2Function, isNull) {
	Matrix2x2 testMat = Matrix2x2(
		0, 0,
		0, 0
	);
	EXPECT_TRUE(testMat.IsNull());
	EXPECT_TRUE(Matrix2x2().IsNull());
	EXPECT_FALSE(Matrix2x2(5).IsNull());
	testMat = Matrix2x2(
		1, 0,
		0, 5
	);
	EXPECT_FALSE(testMat.IsNull());
}

TEST(Matrix2x2Function, isSymmetric) {
	Matrix2x2 testMat = Matrix2x2(
		1, 0,
		0, 1
	);
	EXPECT_TRUE(testMat.IsSymmetric());
	EXPECT_TRUE(Matrix2x2().IsSymmetric());
	EXPECT_TRUE(Matrix2x2(5).IsSymmetric());
	testMat = Matrix2x2(
		1, 0,
		0, 5
	);
	EXPECT_TRUE(testMat.IsSymmetric());
	testMat = Matrix2x2(
		1, 2,
		0, 5
	);
	EXPECT_FALSE(testMat.IsSymmetric());
	testMat = Matrix2x2(
		0, 2,
		0, 0
	);
	EXPECT_FALSE(testMat.IsSymmetric());
	testMat = Matrix2x2(
		0, 2,
		2, 0
	);
	EXPECT_TRUE(testMat.IsSymmetric());
}

TEST(Matrix2x2Function, isAntisymmetric) {
	Matrix2x2 testMat = Matrix2x2(
		1, 0,
		0, 1
	);
	EXPECT_TRUE(testMat.IsAntisymmetric());
	EXPECT_TRUE(Matrix2x2().IsAntisymmetric());
	EXPECT_FALSE(Matrix2x2(5).IsAntisymmetric());
	testMat = Matrix2x2(
		1, 0,
		0, 5
	);
	EXPECT_TRUE(testMat.IsAntisymmetric());
	testMat = Matrix2x2(
		1, 2,
		0, 5
	);
	EXPECT_FALSE(testMat.IsAntisymmetric());
	testMat = Matrix2x2(
		0, 2,
		0, 0
	);
	EXPECT_FALSE(testMat.IsAntisymmetric());
	testMat = Matrix2x2(
		1, 2,
		-2, 5
	);
	EXPECT_TRUE(testMat.IsAntisymmetric());
}

#pragma endregion

#pragma region Matrix3x3

TEST(Matrix3x3, constructor) {
	Matrix3x3 testMat = Matrix3x3();
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			EXPECT_EQ(testMat[i][j], 0);

	testMat = Matrix3x3(5);
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			EXPECT_EQ(testMat[i][j], 5);

	testMat = Matrix3x3(Vector3(1, 2, 3), Vector3(4, 5, 6), Vector3(7, 8, 9));
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			EXPECT_EQ(testMat[i][j], i * 3 + j + 1);

	testMat = Matrix3x3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	);
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			EXPECT_EQ(testMat[i][j], i * 3 + j + 1);

	Matrix3x3 testCopy(testMat);
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			EXPECT_EQ(testCopy[i][j], testMat[i][j]);

	testMat = Matrix3x3::Identity();
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			EXPECT_EQ(testMat[i][j], i == j ? 1 : 0);
}

TEST(Matrix3x3Function, isDiagonal) {
	EXPECT_TRUE(Matrix3x3().IsDiagonal());
	EXPECT_FALSE(Matrix3x3(5).IsDiagonal());
	Matrix3x3 testMat = Matrix3x3(
		1, 0, 0,
		0, 5, 0,
		0, 0, 9
	);
	EXPECT_TRUE(testMat.IsDiagonal());
}

TEST(Matrix3x3Function, isIdentity) {
	Matrix3x3 testMat = Matrix3x3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	);
	EXPECT_TRUE(testMat.IsIdentity());
	EXPECT_TRUE(Matrix3x3::Identity().IsIdentity());
	EXPECT_FALSE(Matrix3x3().IsIdentity());
	EXPECT_FALSE(Matrix3x3(5).IsIdentity());
	testMat = Matrix3x3(
		1, 0, 0,
		0, 5, 0,
		0, 0, 9
	);
	EXPECT_FALSE(testMat.IsIdentity());
}

TEST(Matrix3x3Function, isNull) {
	Matrix3x3 testMat = Matrix3x3(
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	);
	EXPECT_TRUE(testMat.IsNull());
	EXPECT_TRUE(Matrix3x3().IsNull());
	EXPECT_FALSE(Matrix3x3(5).IsNull());
	testMat = Matrix3x3(
		1, 0, 0,
		0, 5, 0,
		0, 0, 9
	);
	EXPECT_FALSE(testMat.IsNull());
}

TEST(Matrix3x3Function, isSymmetric) {
	Matrix3x3 testMat = Matrix3x3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	);
	EXPECT_TRUE(testMat.IsSymmetric());
	EXPECT_TRUE(Matrix3x3().IsSymmetric());
	EXPECT_TRUE(Matrix3x3(5).IsSymmetric());
	testMat = Matrix3x3(
		1, 0, 0,
		0, 5, 0,
		0, 0, 9
	);
	EXPECT_TRUE(testMat.IsSymmetric());
	testMat = Matrix3x3(
		1, 2, 3,
		0, 5, 0,
		0, 0, 9
	);
	EXPECT_FALSE(testMat.IsSymmetric());
	testMat = Matrix3x3(
		0, 2, 3,
		0, 0, 0,
		0, 0, 0
	);
	EXPECT_FALSE(testMat.IsSymmetric());
	testMat = Matrix3x3(
		0, 2, 3,
		2, 0, 0,
		3, 0, 0
	);
	EXPECT_TRUE(testMat.IsSymmetric());
}

TEST(Matrix3x3Function, isAntisymmetric) {
	Matrix3x3 testMat = Matrix3x3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	);
	EXPECT_TRUE(testMat.IsAntisymmetric());
	EXPECT_TRUE(Matrix3x3().IsAntisymmetric());
	EXPECT_FALSE(Matrix3x3(5).IsAntisymmetric());
	testMat = Matrix3x3(
		1, 0, 0,
		0, 5, 0,
		0, 0, 9
	);
	EXPECT_TRUE(testMat.IsAntisymmetric());
	testMat = Matrix3x3(
		1, 2, 3,
		0, 5, 0,
		0, 0, 9
	);
	EXPECT_FALSE(testMat.IsAntisymmetric());
	testMat = Matrix3x3(
		0, 2, 3,
		0, 0, 0,
		0, 0, 0
	);
	EXPECT_FALSE(testMat.IsAntisymmetric());
	testMat = Matrix3x3(
		1, 2, 3,
		-2, 5, 6,
		-3, -6, 9
	);
	EXPECT_TRUE(testMat.IsAntisymmetric());
}


TEST(Matrix3x3Function, Diagonal) {
	Matrix3x3 testMat = Matrix3x3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	);
	EXPECT_EQ(testMat.Diagonal().x, 1);
	EXPECT_EQ(testMat.Diagonal().y, 1);
	EXPECT_EQ(testMat.Diagonal().z, 1);
	testMat = Matrix3x3(
		1, 2, 3,
		0, 5, 0,
		0, 0, 9
	);
	EXPECT_EQ(testMat.Diagonal().x, 1);
	EXPECT_EQ(testMat.Diagonal().y, 5);
	EXPECT_EQ(testMat.Diagonal().z, 9);
}

#pragma endregion

#pragma region Matrix4x4

TEST(Matrix4x4, constructor) {
	Matrix4x4 testMat = Matrix4x4();
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMat[i][j], 0);

	testMat = Matrix4x4(5);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMat[i][j], 5);

	testMat = Matrix4x4(Vector4(1, 2, 3, 4), Vector4(5, 6, 7, 8), Vector4(9, 10, 11, 12), Vector4(13, 14, 15, 16));
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMat[i][j], i * 4 + j + 1);

	testMat = Matrix4x4(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMat[i][j], i * 4 + j + 1);


	Matrix4x4 testCopy = Matrix4x4(testMat);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testCopy[i][j], testMat[i][j]);

	testMat = Matrix4x4::Identity();
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMat[i][j], i == j ? 1 : 0);
}


TEST(Matrix4x4, booleanFunc) {
	EXPECT_TRUE(Matrix4x4().IsDiagonal());
	EXPECT_TRUE(Matrix4x4::Identity().IsDiagonal());

	EXPECT_TRUE(Matrix4x4::Identity().IsIdentity());
	EXPECT_FALSE(Matrix4x4().IsIdentity());

	EXPECT_FALSE(Matrix4x4::Identity().IsNull());
	EXPECT_TRUE(Matrix4x4().IsNull());

	EXPECT_TRUE(Matrix4x4::Identity().IsSymmetric());
	Matrix4x4 testMat = Matrix4x4(Vector4(1, 2, 3, 4), Vector4(5, 6, 7, 8), Vector4(9, 10, 11, 12), Vector4(13, 14, 15, 16));
	EXPECT_FALSE(testMat.IsSymmetric());

	EXPECT_FALSE(Matrix4x4::Identity().IsAntisymmetric());
	testMat = Matrix4x4(Vector4(0, 2, 3, 4), Vector4(-2, 0, 1, 1), Vector4(-3, -1, 0, 1), Vector4(-4, -1, -1, 0));
	EXPECT_TRUE(testMat.IsAntisymmetric());
}

TEST(Matrix4x4, diagonal) {

	Matrix4x4 testMat = Matrix4x4::Identity();
	EXPECT_EQ(testMat.Diagonal().x, 1);
	EXPECT_EQ(testMat.Diagonal().y, 1);
	EXPECT_EQ(testMat.Diagonal().z, 1);
	EXPECT_EQ(testMat.Diagonal().w, 1);

	testMat = Matrix4x4(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	EXPECT_EQ(testMat.Diagonal().x, 1);
	EXPECT_EQ(testMat.Diagonal().y, 6);
	EXPECT_EQ(testMat.Diagonal().z, 11);
	EXPECT_EQ(testMat.Diagonal().w, 16);
}

TEST(Matrix4x4, trace) {

	Matrix4x4 testMat = Matrix4x4::Identity();
	EXPECT_EQ(testMat.Trace(), 4);

	testMat = Matrix4x4(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	EXPECT_EQ(testMat.Trace(), 34);

}

TEST(Matrix4x4, subMat) {

	Matrix4x4 testMat = Matrix4x4::Identity();
	Matrix4x4 subMat = testMat.SubMatrix(0, 0, 2, 2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			EXPECT_EQ(subMat[i][j], testMat[i][j]);

	testMat = Matrix4x4(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	subMat = testMat.SubMatrix(0, 0, 2, 2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			EXPECT_EQ(subMat[i][j], testMat[i][j]);

}

TEST(Matrix4x4, determinant) {

	Matrix4x4 testMat = Matrix4x4::Identity();
	EXPECT_EQ(testMat.Determinant(), 1);

	testMat = Matrix4x4(
		5.f, 2.f, 1.f, 6.f,
		3.f, 8.f, 7.f, 0.f,
		0.f, 5.f, 0.f, 2.f,
		6.f, 4.f, 6.f, 0.f
	);
	EXPECT_EQ(testMat.Determinant(), 496);

}

TEST(Matrix4x4, LoadIdentity) {

	Matrix4x4 testMat = Matrix4x4(
		5.f, 2.f, 1.f, 6.f,
		3.f, 8.f, 7.f, 0.f,
		0.f, 5.f, 0.f, 2.f,
		6.f, 4.f, 6.f, 0.f
	);
	EXPECT_FALSE(testMat.IsIdentity());
	testMat.LoadIdentity();
	EXPECT_TRUE(testMat.IsIdentity());

}


TEST(Matrix4x4, transpose) {

	Matrix4x4 testMat = Matrix4x4::Identity();
	Matrix4x4 testMatTranspose = testMat;
	testMatTranspose.Transpose();
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMatTranspose[i][j], testMat[j][i]);

	testMat = Matrix4x4(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	testMatTranspose = testMat;
	testMatTranspose.Transpose();
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMatTranspose[i][j], testMat[j][i]);

	testMat = Matrix4x4::Identity();
	testMatTranspose = Matrix4x4::Transpose(testMat);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMatTranspose[i][j], testMat[j][i]);

	testMat = Matrix4x4(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	testMatTranspose = Matrix4x4::Transpose(testMat);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			EXPECT_EQ(testMatTranspose[i][j], testMat[j][i]);
}

TEST(Matrix4x4, augment) {




}

TEST(Matrix4x4, gaussJordan) {




}

TEST(Matrix4x4, inverse) {




}

TEST(Matrix4x4, translationMatrix) {

	Matrix4x4 translationMat = Matrix4x4::TranslationMatrix3D({ 1,2,3 });

	EXPECT_EQ(translationMat[0][3], 1);
	EXPECT_EQ(translationMat[1][3], 2);
	EXPECT_EQ(translationMat[2][3], 3);
	EXPECT_EQ(translationMat[2][1], 0);

}

TEST(Matrix4x4, rotationMatrix) {

	/*
		Matrix4x4 rotationMat = Matrix4x4::RotationMatrix3D(PI/2, { 0,0,1 });
		std::cout << rotationMat << std::endl;
		// EXPECT_EQ(rotationMat[1][1], 0);
		// EXPECT_EQ(rotationMat[1][2], -1);
		// EXPECT_EQ(rotationMat[2][1], 1);
		// EXPECT_EQ(rotationMat[2][2], 0);

	*/
}

TEST(Matrix4x4, scalingMatrix) {

	Matrix4x4 scalingMat = Matrix4x4::ScalingMatrix3D({ 1,2,3 });
	EXPECT_EQ(scalingMat[0][0], 1);
	EXPECT_EQ(scalingMat[1][1], 2);
	EXPECT_EQ(scalingMat[2][2], 3);
	EXPECT_EQ(scalingMat[2][3], 0);

}

TEST(Matrix4x4, toQuaternion) {

	Matrix4x4 testMat = Matrix4x4::Identity();
	Quaternion quat = testMat.ToQuaternion();

	EXPECT_EQ(quat.imaginary.x, 0);
	EXPECT_EQ(quat.imaginary.y, 0);
	EXPECT_EQ(quat.imaginary.z, 0);
	EXPECT_EQ(quat.real, 1);


	testMat = Matrix4x4(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	quat = testMat.ToQuaternion();
	std::cout << quat << std::endl;
	EXPECT_EQ(quat.imaginary.x, 0.34);
	//EXPECT_EQ(quat.imaginary.y, -0.69);
	//EXPECT_EQ(quat.imaginary.z, 0.34);
	//EXPECT_EQ(quat.real, 2.18);

}

#pragma endregion
