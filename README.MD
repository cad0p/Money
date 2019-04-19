# Money Payments Aggregator to reduce small sum fees

A prototype system in which a group of buyers and sellers create a "pool" to save on credit/debit card transaction fees (the fixed part), thus making micro (sub-dollar) transactions feasible.


## Getting Started

This project is written in C++, so it works in all major OSes.

A few details on the reasoning on why I made this are on [WHY.MD](WHY.MD)

Keep in mind it's Google Translated for now, the Italian version is here: [WHY_IT.MD](WHY_IT.MD)

### Prerequisites

Just use gcc to compile after cloning this repo

### Installing

There are many variables to customize the results

```
static const int N_b = 100; //Number of buyers
static const int N_s = 10;  // Number of sellers
static const int N_t = 5000;  // Number of transactions a day
static const int DAYS = INFINITY; // Number of days
static const int BUFFER = 80; // Buffer for every transaction
static const int from = 0;
static const int to = 10;

static const double FIXED = 0.1;    // Fixed cost in real money per transaction
static const double VARIABLE = 0.02; // Variable cost of transaction (in percentage)
```


An example of the result:

```
vTransactions: 	2049
Transactions: 	79
Total amount: 	10001.2
Total real amount: 	6582.84
Advantage over system: 	96.1445%
Bank balance: 	139.557
Interest rate: 	0.0212001
max spent: 	167.94
```

## Built With

* [Sublime Text](https://www.sublimetext.com/) - The text editor used
* [Visual Studio](https://visualstudio.microsoft.com/) - To develop initially
* [GitHub Desktop](https://desktop.github.com/) - To manage developement

## Contributing

The following is a copy of PurpleBooth
> Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/cad0p/Money/tags). 

## Authors

* **Pier Carlo Cadoppi** - *Initial work*

See also the list of [contributors](https://github.com/cad0p/Money/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
*  * **Billie Thompson** - *README Template* - [PurpleBooth](https://github.com/PurpleBooth)
* Inspiration
* etc lol
