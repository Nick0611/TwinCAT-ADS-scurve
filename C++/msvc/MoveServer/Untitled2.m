clear
clc
p = csvread('output.csv');
[m,n] = size(p);
v1 = p(1,30:n-1);
p1 = p(1,29:n-2);
v = v1-p1;
[m1,n1] = size(v);
a1 = v(2:n1);
a2 = v(1:n1-1);
a = a1-a2;
plot(p)
figure
plot(v)
figure
plot(a)