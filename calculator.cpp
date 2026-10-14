#include <iostream>
#include <cmath>

// NO AI USED hence the sloppy syntax lol

// Eulers Discount Factor
double discount(double day, double rate) {
	return std::exp(-rate * day / 365);
}

// Discounting Notional Face
double face(double df, double par) {
	return df * par;
}

// General Differences
double basis(double ust, double sofr) {
	return ust - sofr;
}

// Mod Duration, Annualized, for 1% Rate Move
double mod(double day, double rate) {
	return ( day / 365 ) / ( 1 + rate );
}
	

// Main Program, Puts the Data Together
int main() {
	// define varaibles
	double ustrate, sofrrate, ustday, sofrday, ustpar, sofrpar;

	// general welcome text
	std::cout << "\n";
	std::cout << "!!! Welcome to my first Clang++ Fixed Income Calculator !!!\n";
	std::cout << "\n";
	std::cout << "??? This is a Zero Coupon UST versus Fixed Delivery SOFR Swap Basic Calculator ???\n";
	std::cout << "\n";
	std::cout << "??? SOFR Swap (hypothetical borrowed against) is priced like a Zero UST ???\n";
	std::cout << "\n";
	std::cout << "---Type In Inputs Below---\n";
	std::cout << "\n";

	// variable input
	std::cout << "Type in UST Zero Annualized Rate as decimal: ";
	std::cin >> ustrate;
	std::cout << "Type in SOFR Swap Annualized Rate as decimal: ";
	std::cin >> sofrrate;
	std::cout << "Type in UST Days to Maturity: ";
	std::cin >> ustday;
	std::cout << "Type in SOFR Days to Roll: ";
	std::cin >> sofrday;
	std::cout << "Type in Par Notional UST: ";
	std::cin >> ustpar;
	std::cout << "Type in Par Notional SOFR: ";
	std::cin >> sofrpar;

	// discount factor variables
	double ustdf = discount(ustday, ustrate);
	double sofrdf = discount(sofrday, sofrrate);

	// bond-swap price variables
	double ustface = face(ustdf, ustpar);
	double sofrface = face(sofrdf, sofrpar);

	// mod duration variables
	double ustmod = mod(ustday, ustrate);
	double ustmoddollar = ( ustmod / 100 ) * ustface;
	double sofrmod = mod(sofrday, sofrrate);
	double sofrmoddollar = ( sofrmod / 100 ) * sofrface;

	// treasury specific outputs
	std::cout << "\n";	
	std::cout << "---Treasury Zero Outputs---\n";
	std::cout << "\n";
	std::cout << "UST Zero DF is: " << ustdf << "\n";
	std::cout << "UST Zero Price is: " << ustface << "\n";
	std::cout << "UST Zero Total Return is: +$" << basis(ustpar, ustface) << std::endl;
	std::cout << "UST Zero Percentage Mod Exposure for 1% Rate Move is: +/-" << ustmod << "%\n";
	std::cout << "UST Zero Dollar Mod Exposure for 1% Rate Move is: +/- $" << ustmoddollar << "\n";

	// sofr specific outputs
	std::cout << "\n";
	std::cout << "---SOFR Swap Outputs---\n";
	std::cout << "\n";
	std::cout << "SOFR Swap DF is: " << sofrdf << "\n";
	std::cout << "SOFR Swap Price is: " << sofrface << "\n";
	std::cout << "SOFR Swap Total Debt Owed is: -$" << basis(sofrpar, sofrface) << std::endl;
	std::cout << "SOFR Swap Percentage Mod Exposure for 1% Rate Move is: +/- " << sofrmod << "%\n";
	std::cout << "SOFR Swap Dollar Mod Exposure for 1% Rate Move is: +/- $" << sofrmoddollar << "\n";

	// extra variables for basis outputs
	double usttr = basis(ustpar, ustface);
	double sofrdebt = basis(sofrpar, sofrface);

	// treasury versus sofr outputs
	std::cout << "\n";
	std::cout << "---Treasury Zero vs SOFR Swap Outputs---\n";
	std::cout << "\n";
	std::cout << "Treasury Zero Matures in " << basis(ustday, sofrday) << " more/less days that SOFR Swap" << std::endl;
	std::cout << "Treasury Zero minus SOFR Swap Rate Basis is: " << 10000 * basis(ustrate, sofrrate) << "bps" << std::endl;
	std::cout << "Treasury Zero minus SOFR price basis is: $" << basis(ustface, sofrface) << std::endl;
	std::cout << "Treasury Zero Total Return minus SOFR Swap Debt basis is: $" << basis(usttr, sofrdebt) << std::endl;
	std::cout << "Treasury Zero Mod Exposure minus SOFR Swap Mod Exposure Basis is: " << 100 * basis(ustmod, sofrmod) << "bps" << std::endl;
	std::cout << "Treasury Zero Dollar Mod Exposure minus SOFR Swap Mod Dollar Exposure Basis is: $" << basis(ustmoddollar, sofrmoddollar) << std::endl;

	// duration hedge ratio variable
	double modratio = ustmoddollar / sofrmoddollar;

	// duraton hedge outputs
	std::cout << "\n";
	std::cout << "---Duration Hedge Outputs---\n";
	std::cout << "\n";
	std::cout << "The Current Treasury Zero over SOFR Swap Duration Hedge Ratio is: " << modratio << "\n";
	std::cout << "This Means for every 100 of Treasury Zeroes you need " << 100 * modratio << " SOFR Swap!";

	// Return 0 to make it Boolean Valid
	return 0;
}
