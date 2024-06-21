*1 Overview

In this assignment we concentrate on features that will make this application more user-friendly. We will add support to buy and sell shares in a portfolio on any date, and examine the total money invested and the total value of the portfolio on any date. We will add support for some other stock statistics. Lastly we will add a feature to plot the performance of a portfolio over time.

### 2 Features to Add

#### 2.1 Portfolios

A portfolio of stocks is simply a collection of stocks (e.g. 10 shares of company X, 20 shares of company Y, etc.). The total value of a portfolio is then the sum of the values of its individual holdings. Thus the value of a portfolio, much like individual stocks, also changes with time. As an example, we hear about the S&P 500, Dow Jones Industrial and NASDAQ in the news, quoted to gauge the health of the overall stock market. These three "indices" are nothing more than portfolios of stocks of specific companies, which have been found to be reasonable barometers of the health of the overall stock market and economy, or a specific part of them (e.g. technology).

An individual investor may track multiple portfolios: a retirement portfolio, a college-savings portfolio, health savings portfolio, etc.

Stocks may be added (bought) to or removed (sold) from a portfolio. As such, the contents of a portfolio (its composition), and the value of a portfolio change with time.

In this assignment you must add support for portfolios that allow the following features:

- Purchase a specific number of shares of a specific stock on a specified date, and add them to the portfolio
- Sell a specific number of shares of a specific stock on a specified date from a given portfolio
- Determine the composition of a portfolio at a specific date. Note that the composition may change over time. The composition must include (a) the list of stocks and (b) the number of shares of each stock
- Determine the value of a portfolio on a specific date (to be exact, the end of that day). The value for a portfolio before the date of its first purchase would be 0, since each stock in the portfolio now was purchased at a specific point in time.
- The distribution of value of a portfolio on a specific date (to be exact, the end of that day). The distribution of value should include (a) the stock itself (b) the value of each individual stock in the portfolio. The sum of the values in (b) should equal to the value of that portfolio on that date.
- Persist a portfolio so that it can be saved and loaded (i.e. save to and retrieve from files)

The files used to save and retrieve portfolios must be human-readable, text files. While you are free to determine the format of these files, using standard formats like XML or JSON has natural advantages. In any case, a user should be able to create such a file outside of the program using a text editor and have your program load it in.

#### 2.2 Rebalance a Portfolio

Let us assume that an investor decided to create a portfolio of 4 stocks: Netflix, Google, Microsoft and Apple. They wanted the money invested in this portfolio equally among these four stocks. For example, if they had $1000 to invest, they would buy $250 worth of shares of each of the four companies. On the date on which this portfolio was made, the prices of these stocks were $10, $25, $10 and $50 respectively. Thus the portfolio would be made of 25 shares of Netflix, 10 shares of Google, 25 shares of Microsoft and 5 shares of Apple respectively.

However as time passes, each of these stocks gain and lose value. As a result, on a certain specific date the value of each of these stocks in this portfolio may not be exactly one-fourth of the total value of the portfolio on that date. In order to stay on their goal, the investor decides to re-balance their portfolio. Rebalancing involves selling some stock of companies that are over-represented to buy stock of companies that are under-represented.

For example, let us assume that on a particular date, the price per share of these four companies were $15, $30, $10 and $30 respectively. Thus the values of these stocks (price per share multiplied by number of shares) would be $375, $300, $250 and $150 respectively, bringing the total value of the portfolio to $1075. If the intended distribution of these stocks in the portfolio was supposed to be (25%, 25%, 25%, 25%), the portfolio should have $268.75 worth of each stock. Therefore, the investor will have to sell $106.25 worth of Netflix stock (7.0833 shares) and $31.25 worth of Google stock (1.0417 shares)to purchase $18.75 worth of Microsoft stock (1.875 shares) and $118.75 (3.9583 shares) of Apple stock. Alternatively, if the intended distribution of these stocks in the portfolio was supposed to be (40%, 20%, 20%, 20%), the portfolio should have $430, $215, $215 and $215 worth of Netflix, Google, Microsoft and Apple stock respectively. Therefore, the investor will have to sell $85 worth of Google stock (2.8333 shares) and $35 worth of Microsoft stock (3.5 shares) to purchase $55 worth of Netflix stock (3.6666 shares) and $65 worth of Apple stock (2.1666 shares).

After balancing, the distribution of value of the portfolio should match the intended weights (you can use this as a way to test).

**The rebalancing should happen on a specified date, with the specified weights.**

#### 2.3 Performance Over Time

One of the most popular ways to analyze the success (or lack thereof) of investing is to view how a stock or a portfolio has performed over a period of time. Although it is possible to repeatedly query the value of a stock/portfolio using the above features, seeing the performance "at a glance" offers a better way.

One way to visualize this is by using a bar or line chart. Here is an example of a horizontal bar chart using text:

```
Performance of portfolio XXX from YYY to ZZZ

Jan 2010: *****
Feb 2010: ***
Mar 2010: ********
Apr 2010: ******
May 2010: *******
Jun 2010: ********
Aug 2010: *********
Sep 2010: ***********
Oct 2010: ************
Nov 2010: **********
Dec 2010: **************

Scale: * = 1000
```

Note the various elements of this chart:

- The title of the barchart specifies the name of the stock/portfolio (XXX), and the time range (YYY to ZZZ).
- Each line starts with a timestamp. All timestamps are of the same length, so that the ':' symbols align
- The number of lines is decided by the timespan desired. The scale of the timestamps (i.e. each month of a year, every 3 months, every day, etc.) is decided by the timespan, so that bar chart has at least 5 lines but no more than 30 lines. The starting and ending dates of the timespan must be part of the chart. The chart's minimum resolution is "day" (i.e. you do not have to chart the intra-day prices of stocks/portfolio). This restriction may be lifted if the time window specified is less than 5 days.
- The number of asterisks on each line is a measure of the value of the portfolio at that timestamp. If the timestamps are dates then the value is computed at the end of that day. If the timestamps are months then the value is computed at the last working day of that month. If the timestamp are years then the value is computed on the last working day of that year.
- The end of the bar chart shows the scale in terms of how many dollars are represented by each asterisk. The scale of the horizontal axis is decided by the range of values of the portfolios, so that there are no more than 50 asterisks on each line.
- The scale may be absolute (one asterisk is equal to 1000) or relative to a base amount (one asterisk is 2000𝑚𝑜𝑟𝑒𝑡ℎ𝑎𝑛𝑎𝑏𝑎𝑠𝑒𝑎𝑚𝑜𝑢𝑛𝑡𝑜𝑓 100000). This will allow you to plot the bar chart over small or large ranges of portfolio values. The last line of the barchart should clearly mention which type of scale it is.

Your program must support drawing (as text on the screen) a bar chart according to the above specifications, for a specific portfolio and a specified time range.

#### 2.4 Text-based view

The text-based view should still work, and should incorporate all the features from this assignment as well.

Specifically, a user should be able to: * Create a portfolio of stocks and add/remove stocks by purchasing or selling.

- Find the composition, value and distribution of value of a portfolio on a specified date.
- Save an existing portfolio and retrieve a previously saved portfolio.
- Inspect whether a stock lost or gained on a specified day.
- Compute the x-day moving average for a given stock.
- Compute and report the x-day crossover days for a given stock within a specified period.
- Do all of the above for any stock that is available in the AlphaVantage API.
- Allow balancing of an existing portfolio with the given weights **on a specified date** .
- Plot a bar chart that illustrates the performance of a given stock or existing portfolio over a given time frame.

### 3 Design

We expect your design to follow the MVC architecture. Adding feature logic code in the view will cost you points! A good implementation of MVC allows us to substitute one part with minimal changes to the others.

Your model and controller should have had an interface: if it did not, please add it to your design now. Your program should now have a formal view, with an interface and an implementation. This way, the controller communicates with the model and the view in a principled way.

**You are allowed to enhance or change your existing design. However we expect you to follow the SOLID principles as much as you can. When you do need to edit/enhance your design, you should document and justify the changes, both in the code and the DESIGN-README file. You will be graded on the number and extent of design changes.**

Do not compromise on your design in a quest to make a snazzy, feature-rich, polished program! A polished product may not get you any extra credit, but a poorly designed program will cost you!

### 4 Testing

We expect you to test all parts of your program, just as thoroughly as other assignments. We expect you to come up with appropriate testing strategies to do this (we are purposefully not giving you specific testing examples and the expected results).**