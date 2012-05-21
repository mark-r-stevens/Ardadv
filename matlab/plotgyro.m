
A = csvread('Capture.txt');

t1 = A(:,1);
t2 = A(:,2);
dt1 = conv(t1,[1,-1], 'valid');
dt2 = conv(t2,[1,-1], 'valid');
x = A(:,3);
y = A(:,4);
z = A(:,5);

sz = conv(z, [1 2 1]/4, 'valid');

figure(1), plot(t1, x, 'r-', t1, y, 'b-', t1, z, 'g-');
legend('x', 'y', 'z');
ylabel('response');
xlabel('time');


figure(2), plot(cumsum(z/50))
ylabel('angle');
xlabel('time');

clear all;
close all;
A = csvread('Capture.txt');
a = A(:,2);
z = -A(:,3);
t = 1:length(a);
dt = conv(A(:,1),[1,-1], 'valid');
figure(1), plot(t, a, 'r-', t, cumsum(z/mean(dt)), 'g-');
legend('servo', 'gyro');
ylabel('angle');
xlabel('time');

