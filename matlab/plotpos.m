% Read in the output of device/platform/dfrobot/state/test01
%
A = csvread('Capture.txt');

% Pull out the columns
%
x = A(:,4);
y = A(:,5);
theta = A(:,6);

% Pull out the distance
%
d = A(:,7);

% Plot the distance
%
plot(1:330, d, 'b-', 1:330, x, 'r-')
legend('ultrasonic', 'x position')

% Plot the x/y position
%
plot (x, y, 'r.');
axis([-1 1 -1 1]);

