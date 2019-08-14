x=linspace(1,40,40);
recursion_java=[2.25
0.66
0.75
0.96
1.03
1.56
2.43
4.01
9.52
16.26
20.47
31.85
11.86
5.92
7.71
12.2
29.82
33.97
56.73
94.84
142.9
235.13
423.73
196.74
287.65
509.23
797.32
1194.49
1912.96
3332.59
5372.93
8506.73
14428.32
22412.3
35704.48
57167.13
92002.67
151422.74
243574.46
390990.18
];

iteration_java=[2.37
0.94
0.82
0.84
0.88
0.92
0.94
0.97
1.08
0.97
1.09
1.24
0.94
0.95
1.33
1.29
1.19
1.23
1.38
1.43
1.46
1.36
1.33
1.06
1.04
1.45
1.63
1.52
1.15
1.64
1.6
1.59
1.69
1.72
1.66
1.72
1.45
1.81
1.64
1.86
];

python_iteration=[1.91
0.95
0.95
0.95
0.95
1.19
0.95
2.15
1.91
1.91
2.15
1.91
2.15
1.91
3.1
3.1
3.1
2.86
3.1
3.1
3.81
4.05
4.05
3.1
4.05
3.81
4.05
4.05
5.01
5.01
5.01
5.01
5.01
5.01
5.01
5.01
5.96
5.96
5.01
5.96
];

python_recursion=[0.95
0.95
1.91
2.15
1.91
2.86
7.15
9.06
15.02
13.83
35.05
41.01
74.86
110.86
169.04
265.12
418.9
667.1
1072.88
1881.84
2896.07
4870.18
7611.99
11583.09
17737.15
28015.14
46298.98
72050.09
115397.93
185763.12
300493
485308.89
800179
1275718.21
2118418.93
3351107.12
5434885.98
8806936.98
14299402
23204005.96
];


plot(x,recursion_java,'Marker','.','MarkerSize',14)
hold on
plot(x,iteration_java,'-y','Marker','*','MarkerSize',14)
plot(x,python_recursion,'g','Marker','.','MarkerSize',14)
plot(x,python_iteration,'r','Marker','.','MarkerSize',14')
title(['Variation of the Run Time'])
xlabel('Problem size')
ylabel('Run-time(microseconds)')
legend('Java Recursion','Java Iteration','Python Recursion','Python Iteration')
