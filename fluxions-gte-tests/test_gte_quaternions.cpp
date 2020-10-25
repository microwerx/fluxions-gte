#include <catch2/catch.hpp>
#include <fluxions_gte_quaternion.hpp>

TEST_CASE("Quaternions", "[quaternions]") {
	using Fluxions::Quaternionf;
	const Quaternionf qzero;
	const Quaternionf qone{ 1.0f };
	const Quaternionf q2{ 1.0f, 2.0f, 3.0f, 4.0f };
	Quaternionf q1{ 0.0f, 0.0f, 0.0f, 0.0f };

	REQUIRE(qzero == q1);
	q1.a = 1.0f;
	REQUIRE(qzero != q1);
	q1 = Quaternionf{ 1.0f, 2.0f, 3.0f, 4.0f };
	REQUIRE(q1 == q2);

	REQUIRE(5.0f * qzero == qzero);
	REQUIRE(1.0f * q2 == q2);
	REQUIRE(2.0f * q2 != q2);

	Quaternionf qposfive{ 5.0f };
	Quaternionf qnegfive{ -5.0f };
	Quaternionf s;
	s = 5.0f + qzero;
	REQUIRE(s == qposfive);
	s = qzero + 5.0f;
	REQUIRE(s == qposfive);
	s = 5.0f * qone;
	REQUIRE(s == qposfive);
	s = qone * 5.0f;
	REQUIRE(s == qposfive);
	s = qzero - 5.0f;
	REQUIRE(s == qnegfive);
	s = 5.0f - qzero;
	REQUIRE(s == qposfive);

	Quaternionf x{ 0.0f, 1.0f, 0.0f, 0.0f };
	Quaternionf y{ 0.0f, 0.0f, 1.0f, 0.0f };
	Quaternionf z{ 0.0f, 0.0f, 0.0f, 1.0f };
	Quaternionf w{ 0.0f, 1.0f, 1.0f, 1.0f };
	Quaternionf slerped = slerp(x, y, 0.1f);
	Quaternionf squaded = squad(x, y, z, w, 0.1f);

	Quaternionf xy = x * y;
	REQUIRE(xy == z);
	Quaternionf yz = y * z;
	REQUIRE(yz == x);
	Quaternionf zx = z * x;
	REQUIRE(zx == y);
	REQUIRE(y * x == -xy);
	REQUIRE(z * y == -yz);
	REQUIRE(x * z == -zx);
}
