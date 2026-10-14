# 📑 Fixed-Income Risk & Hedge Calculator (`Clang++`)

Welcome to my first fixed-income portfolio risk analytics calculator! Built in C++, this tool evaluates the relative pricing, risk profile, and delta hedging requirements between a **US Treasury Zero-Coupon Bond** and a **SOFR (Secured Overnight Financing Rate) Swap**. 

The calculator takes institutional market inputs—such as annualized fractional yields, actual days to maturity, and par face value—and derives continuous pricing metrics alongside first-order interest rate risk profiles.

---

## 🧮 Financial Methodology & Mathematical Formulas

This application blends continuous discounting models with fixed-income duration metrics to evaluate and hedge cash exposures across parallel rate shocks.

### 1. Pricing Mechanics (Euler's Discount Factor)
Unlike coupon-bearing securities, a zero-coupon bond is priced purely on the time value of money pulled from maturity back to today. The calculator utilizes **Euler’s continuous discounting model**:

\[\text{DF} = e^{-r \times \left(\frac{\text{Days}}{365}\right)}\]

\[\text{Bond Price (Current Market Value)} = \text{DF} \times \text{Par Notional}\]

*Where:*
* r = Annualized yield to maturity (inputted as a decimal fraction).
* Days = Exact days remaining until maturity or position roll.

### 2. Percentage Risk Model (Modified Duration)
Modified Duration measures the percentage price volatility of a bond relative to a 100-basis-point (1%) parallel shift in the underlying yield curve. For an annualized structure, it follows the relationship:

\[\text{Modified Duration (Years)} = \frac{\text{Days} / 365}{1 + r}\]

*Note: Since the pricing framework utilizes continuous Euler compounding (e), Macaulay Duration matches the time fraction (Days / 365), aligning the percentage change profile tightly with time decay.*

### 3. Dollar Risk Exposure (Dollar Duration)
Percentage sensitivity must be converted into actual capital at risk to facilitate trading calculations. **Dollar Duration** determines the exact monetary volatility of the asset per 1% absolute yield move:

\[\text{Dollar Mod Exposure} = \left(\frac{\text{Modified Duration}}{100}\right) \times \text{Bond Price}\]

This value represents the estimated cash gained or lost if market interest rates experience a parallel shock of 100 basis points.

### 4. Risk Mitigation (Duration Hedge Ratio)
To perfectly insulate a Treasury position from market interest rate fluctuations using a SOFR Swap, the overall dollar risk of both positions must balance out to a net cash variance of zero. The application extracts this transaction volume using a **Dollar Duration Ratio**:

\[\text{Hedge Ratio} = \frac{\text{Dollar Duration}_{\text{Treasury}}}{\text{Dollar Duration}_{\text{SOFR Swap}}}\]

* **Execution Interpretation:** For every 100 units of par value held in the underlying US Treasury, you must execute exactly (100 × Hedge Ratio) par units of the SOFR Swap in the **opposite direction** (e.g., Long Treasury vs. Short Swap / Pay Fixed) to run a duration-neutral book.

---

## 💻 Technical Execution & Compilation

The project is packaged as a lightweight standalone execution script written in standard C++. 

### Prerequisites
Ensure you have a C++ compiler installed on your local environment (such as `Clang++` or `G++`).

### Terminal Commands
To compile and launch the utility locally from your command line terminal, execute the following actions:

```bash
# Compile the source script using Clang++
clang++ -std=c++17 main.cpp -o fi_calculator

# Run the compiled executable binary
./fi_calculator
```

---

## 🛠️ Inputs Checklist
To get optimal, mathematically sound analytics out of the application interface, make sure your terminal inputs meet the following parameters:
* **Yield / Interest Rates:** Inputted as a raw decimal format rather than a whole integer (e.g., enter `4.5%` as `0.045`).
* **Days to Maturity:** Inputted as the true counting number of calendar days left until settlement or position roll.
* **Par Values:** Inputted as the total desired face value structure of the financial instrument (e.g., standard baseline contracts scale out at `100`).
