Team Name
Time Bandits

Team Members
Benjamin Tomczak
Manato Igawa
Maximilian Preble

Project Title
Reliable Retail

Problem Statement
We aim to enable the efficient and scalable discovery of significant patterns common to “successful interactions” in past transaction data. These patterns will be used to analyze whether new transactions are likely to be successful. A “successful interaction” is defined as a transaction that leads to repeat business—identified by the same customer ID appearing on subsequent, distinct transactions. Specifically, the project focuses on analyzing factors such as quantity, price, time, country, and cancellations to determine their correlation with repeat purchases.

Motivation
Product purchases represent a major opportunity for e-commerce platforms, but they also come with challenges such as high return rates and customer dissatisfaction due to poor product recommendations. A system that learns from successful past transactions can help minimize returns and improve customer satisfaction by identifying and promoting “gift products with low return risk and high probability of success.”

Features and Success Criteria
We define success by our ability to identify patterns in transactions that frequently lead to repeat purchases. New transactions will be scored based on their similarity to these patterns. The top n similar transactions will be ranked and presented, prioritizing those linked to the most repeat customers. Additionally, the solution’s effectiveness will be evaluated based on efficiency in terms of time and space.

Data
We are using the publicly available Online Retail dataset from the UCI Machine Learning Repository:
https://archive.ics.uci.edu/dataset/352/online+retail

This dataset includes columns such as InvoiceNo, StockCode, Description, Quantity, InvoiceDate, UnitPrice, CustomerID, and Country, capturing detailed e-commerce transaction information.

Tools
We will be developing the solution in C++. Additional tools or frameworks may be considered for data handling, but the primary implementation will be in a compiled language for performance.

Visuals
The user interface will be a menu-driven ASCII program, allowing users to interact with the data processing system through the command line. Example:
===========================================
Reliable Retail      
===========================================
Select an option:

1. Load Transaction Data
2. Vectorize Transactions
3. Build Similarity Index
4. Score New Transaction
5. Show Top-N Similar Transactions
6. Visualize Success Patterns
7. Export Results
8. Exit

Enter your choice [1-8]: _

                             _        ,
                            (_\______/________
                               \-|-|/|-|-|-|-|/
                                \==/-|-|-|-|-/ 
                                 \/|-|-|-|,-' 
                                  \--|-'''    
                                   \_j________
                                   (_)     (_) 
                                   
Source: https://ascii.co.uk/art/shopping

Data Structures and Algorithmic Strategy
Transactions are stored in a table, where each row represents a transaction and each column corresponds to an attribute. A hash map will be used to store the purchase history of each customer, enabling customer searches in O(1) time. Transactions can be vectorized into arrays according to user-defined parameters. This allows users to compare transaction similarity for better insight into purchasing behavior.

Distribution of Responsibility and Roles
Benjamin: Setup code, Video walkthrough and post-production.

Manato: Original idea proposal and codebase contributions.

Maximilian: Coding and overall project organization.
