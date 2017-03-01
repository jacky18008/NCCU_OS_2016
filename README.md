# NCCU_OS_2016
It is about a final project of NCCU OS 2016

It's a course project of Operating System held by NCCU CS,
I finish it together with 黃冠融, and give big appreciate to him.

In this project, we tried to build a program that simulates managing a swimming pool.
In this simulator, customer will come in some arriving rate set by user,
take a basket, find an empty bathhouse to change their swim clothes, go swimming, 
find an empty bathhouse to change their street clothes, and get out.

We use multithread to moniter our resources: basket and bathhouse,
and using a changed Knuth Thm to generate time values that fit Poisson's Process.
