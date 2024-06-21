### 1 Overall Vision

Gone are the days when one could put money in a bank account and see it grow with interest. One of the very few ways to grow money these days is to invest in the stock market. Such investments can be found virtually everywhere: retirement accounts, college savings plans, health savings accounts, etc. To be successful, one must understand what stock is and how it is traded.

However it is intimidating for a newbie to invest in the stock market. Unlike a savings account, it is possible to lose money in the stock market, in pursuit of greater growth. In order to invest in the stock market, one must have a basic understanding of how stocks work, how investments work, and how to strategize investment. There is no dearth of books, blogs and articles that give investment advice. This advice ranges from simple invest-and-forget ideas to devoting hours each day looking at data and charts. One could hire professional help (a financial broker), but that costs more money.

We will write an application that helps users who are new to investing to learn about how money could grow, in the style of "virtual gambling". Similar to virtual gambling, our application will not use real money and investment. Instead it will allow the user to create investment portfolios, try out buying and selling of stock, and various investment strategies to see how they can grow (or shrink) their money with time.

### 2 Introduction to stocks

In its simplest form, a stock of a company is a part of ownership in that company. Ownership is divided into shares, where a share represents a fraction of the total ownership. For example, Apple has about 16.07B shares. So if you own 100 shares, you own about 6.222𝑥10−9 % of the company (and it would be worth about $15000 today). As a shareholder, you are an investor in the company. An investor sends money to the company to buy some of its stock, and gets part ownership in return. The total money invested in the stock (money spent buying it) is called the cost basis of the purchase. The value of the stock on a particular day is the money the investor would receive if he/she sold the stock on that day.

When the company performs well (e.g. it makes a profit, it expands its business, does business with more money, etc.) the price of the stock goes up because its value in the stock market increases (everybody wants to own that stock). When an investor sells stocks whose prices have risen above their cost bases, they make a profit (they get more money than they had paid to buy the stock earlier). An investor may also benefit in another, unrelated way. Many companies share some of their profits as dividends with their investors. This is not directly related to the price of stock (i.e. the price of the stock may go down, even as the company distributes dividend to its investors). Some companies distribute dividends; others do not. Although this is another way to earn money through investment, we will not consider this type of dividend-based income in this application.

Thousands of companies' stock are available in several stock markets around the world. In addition to individual stocks, an investor can also buy mutual funds and exchange-traded funds. These funds are combinations of several company stocks (called a portfolio of stocks). For example a mutual fund may contain stocks of 500 companies based on some preferences. Investing in a portfolio of stocks reduces risk (if 10 of those companies suffer price declines in the stock market, the overall loss to the investor is less severe because the other 490 companies have remained approximately the same price as the day before). On the other hand, it can also reduce profit (if 10 of those companies soar at the stock market, the overall gain to the investor is averaged out by the gains and losses of the other 490 companies).

### 3 Stocks

Each publicly traded company's stock is given a unique "ticker symbol" which is used to trade it (for example, Apple Inc. is AAPL, Microsoft is MSFT). The price of stock keeps changing all day depending on how many people want to own that stock versus how many people want to sell their shares. The behavior of a US stock during a day can be understood by its opening price (at 8am EST when the New York Stock Exchange opens for business), its closing price (at 4pm EST when the NYSE closes for regular business), its low and high price (during the day). At any point in time, the total value of an investor's holdings of a stock is simply the price of the stock at that time, multiplied by the number of shares of that stock that the investor owns. Usually several prices are available for a given stock: the opening price (its price when the stock exchange opened on that date), the closing price (its price when the stock exchange closed for trading on that date), the real-time price (the price at a certain time on that date) and others.

#### 3.1 Stock Trend Statistics

Given a specific stock, it is possible to compute and report the following statistics on it:

- Over a period of time, did the stock gain or lose (closing prices only)
- On a given day, what is the x-day moving average (for a given positive value of x)? The x-day moving average is the average of the last x days (starting from the given date). Note that this corresponds to the last x days when the stock prices are available.
- Over a specified period of time, what days are "x-day crossovers"? An x-day crossover happens when the closing price for a day is greater than the x-day moving average for that day. A crossover signals a "buy" opportunity. A crossover can be defined over any period of time, although the 30-day period (i.e. the 30-day crossover) is usually popular.

### 4 What to do

In this set of assignments, we will build this application in the model-view-controller style. However instead of concentrating on the model in one assignment and the view in the next, we will attempt to build this application end-to-end in each assignment. Future assignments will then add "features" to our program, affecting multiple layers accordingly to deliver an progressively enhanced program.

Your objective in this assignment is to build a program that has the following features:

- Allow a user to examine the gain or loss of a stock over a specified period.
- Allow a user to examine the x-day moving average of a stock for a specified date and a specified value of x.
- Allow a user to determine which days are x-day crossovers for a specified stock over a specified date range and a specified value of x.
- Allow a user to create one or more portfolios with shares of one or more stock, and find the value of that portfolio on a specific date. You can assume that all the stocks and their quantities will exist on that date.

#### 4.1 User interface/interactivity

Your program must have a suitable text-based interface that allows a user to use all of the above features. The interface must be interactive (i.e. a text-based interface is different from a command-line interface that accepts all inputs in one go and responds). You have complete freedom to design the details of this user interface. However it is important to offer reasonable usability (e.g. a typo causing your program to crash, expecting the user to enter long unwieldy inputs where it is easy to make mistakes, etc. are not reasonable).

**There is one restriction that your program must support: most brokers do not allow a client to directly purchase a fractional amount of shares. Keep in mind that this is a restriction that is user-facing: conceptually buying fractional shares is no different than buying whole shares. Think about how you will incorporate this in your design.**

#### 4.2 Design and Testing

We expect your design to be well-thought out and based on Model-View-Controller. You are expected to apply various design principles, patterns and ideas that you have learned in this course. We are not expecting usage of a specific idea or pattern, but instead looking for an appropriate design. Keep in mind that you may be asked to add new features or enhance existing features in the future. Writing readable, well-structured, well-documented code is still required: you will be graded on all of these criteria.

We expect you to test all parts of your program, just as thoroughly as other assignments. We expect you to come up with appropriate testing strategies to do this (we are purposefully not giving you specific testing examples and the expected results).

As you have complete design freedom, we will not be auto-grading this set of assignments (except for style).

#### 4.3 Getting the stock data

Your program can obtain stock data from various sources. The user may manually enter stock prices in a suitable fashion, provide the data in files/databases, etc.

Several services are available for stock price data. Yahoo and Google are two popular websites that offer financial data. They have a web-based API to query stock-related data. Such an API works with a normal link (URL) that contains some data, and returns (instead of a web page) data in a specific format.

You have been provided with a simple program that uses one such API: Alpha Vantage. The program shows you how to create a URL and process what it returns from within a Java program. Please read the accompanying documentation in comments to understand how it is working. You are allowed to use this service as you see fit (you must obtain a free API key for this. Follow the directions in the given program). You are required to incorporate this API into your program in a suitable way, such that the stock data comes from it. **Remember that the free API restricts the number of queries per hour: you have to find a suitable way to work with this!** Telling the user every time to simply wait and try again later is not good design (although occasionally you may choose to do this). It is also not a good idea to make your program dependent on an internet connection for it to function: remember that the API only provides you historical data (i.e. data that does not change).

#### 4.4 Example Data for Testing

The AlphaVantage API has the ability to provide data in a csv format. Such data can be directly saved as a csv file and opened in a spreadsheet program like Excel. After creating such a file for a given stock, one can then use Excel formulas to compute the quantities in Section 3.1.

For demonstration purposes, such a file has been provided to you with data downloaded from the API for the GOOG stock. You may create other test data similarly. This will help you to write tests for your code.

#### 4.5 What you can use

You are allowed to use any classes within the JDK. You are not allowed to use any classes outside the JDK. One exception to this rule is JUnit.