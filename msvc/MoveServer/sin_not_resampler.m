clc
clear
req_m1 = ones(1,540);
for t = 1 : 1 : 540
    req_m1(t) = 1000 * sin(t*3.1415926 / 180.0) ;
end
[m,n] = size(req_m1);
v1 = req_m1(1,30:n-1);
p1 = req_m1(1,29:n-2);
v = v1-p1;
[m1,n1] = size(v);
a1 = v(2:n1);
a2 = v(1:n1-1);
a = a1-a2;
plot(req_m1)
figure
plot(v)
figure
plot(a)