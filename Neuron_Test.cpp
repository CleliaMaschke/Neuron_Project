#include "Neuron.hpp"
#include <gtest/gtest.h>

TEST(Neuron_Test, calculate_potential) {
	Neuron n1;
	Neuron n2;
	n1.potential = potential_seuil + 1;
	n2.potential = 0.0;
	n1.update(0.2, 1.01, 100);
	EXPECT_EQ(n2.potential, J);

}

int main (int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
