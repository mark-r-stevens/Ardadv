
clear all;
close all;
A = csvread('Capture.txt');
t = A(:,1);
servo   = A(:,2);
gyro = -A(:,3);
compass = -(A(:,4) - 135);
t = 1:length(servo);
dt = conv(A(:,1),[1,-1], 'valid');
figure(1), plot(t, servo, 'r-', t, compass, 'g-', t, cumsum(gyro/13), 'b-');
legend('servo', 'magnetometer', 'gyroscope');
ylabel('angle');
xlabel('time');

combo3 = compass;
var_compass = 0.9;
var_gyro=0.119,
compass_predicted = compass(1);
compass_updated = compass(1);
var_filter_updated=0;
for i=2:length(compass)
    
    compass_predicted = compass_updated + gyro(i) / 13;
    var_filter_predicted = var_filter_updated + var_gyro;
    
    if (abs(compass_predicted-compass(i))> 20)
        disturbed=true;
    else
        disturbed=false;
    end
    
    if (disturbed)
        kalman_gain=0;
    else
        kalman_gain=var_filter_predicted/(var_filter_predicted+var_compass);
    end
    
    compass_updated=compass_predicted+kalman_gain*(compass(i)-compass_predicted);
    var_filter_updated=var_filter_predicted+kalman_gain*(var_compass-var_filter_predicted);
    
    combo3(i)=compass_updated;
end
figure(4), plot(t, servo, 'r-', t, combo3, 'b-');
legend('servo', 'combination');
ylabel('angle');
xlabel('time');

combo = compass;
combo2 = compass;
previous = combo(1);
for i=2:length(compass)
    predicted = previous + gyro(i) / 13;
    diff = abs(predicted - compass(i));
    if (diff < 20)
        predicted = compass(i);
    end
    previous = predicted;
    combo(i)  = predicted;
    combo2(i) = 0.9 * combo2(i-1) + 0.1 * predicted; 
end
figure(2), plot(t, servo, 'r-', t, combo, 'b-');
legend('servo', 'combination');
ylabel('angle');
xlabel('time');
figure(3), plot(t, servo, 'r-', t, combo2, 'b-');
legend('servo', 'combination');
ylabel('angle');
xlabel('time');


sz = heading;
sz2 = heading;
for i=2:length(sz)-1
    %sz(i) = 0.1 * sz(i) + 0.9 * sz(i-1);
    sz2(i) = median([sz(i-1) sz(i) sz(i+1)]);
end

sz2 = heading;
for i=2:length(heading)
    tmp = heading(i-1) + gyro(i);
    if (abs(tmp - heading(i)) > 15)
        sz2(i) = tmp;
    end
end
figure(2), plot(t, servo, 'r-', t, sz2, 'g-');
legend('servo', 'average');
ylabel('angle');
xlabel('time');

 Q_angle  =  0.001; %0.001
 Q_gyro   =  0.003;  %0.003
 R_angle  =  0.03;  %0.03

 combo4 = compass;

 x_angle = compass(1);
 x_bias = 0;
 y = 0;
 P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
 dt = 1;
 z = 0; 
 S = 0;
 K_0 = 0;
 K_1 = 0;
 
 for i=2:length(heading)
     
     newAngle = compass(i);
     newRate = gyro(i) / 13;
     
     x_angle = x_angle + (newRate - x_bias);
     P_00 =  P_00 - (P_10 + P_01) + Q_angle;
     P_01 =  P_00 - P_11;
     P_10 =  P_00 - P_11;
     P_11 =  P_00 + Q_gyro;
     
     y = newAngle - x_angle;
     S = P_00 + R_angle;
     if (S < 0.0001)
         S = 1;
     end
     K_0 = P_00 / S;
     K_1 = P_10 / S;
     
     x_angle = x_angle + K_0 * y;
     x_bias  = x_bias +  K_1 * y;
     P_00 = P_00 - K_0 * P_00;
     P_01 = P_01 - K_0 * P_01;
     P_10 = P_10 - K_1 * P_00;
     P_11 = P_11 - K_1 * P_01;
     
     combo4(i) = x_angle;
 end
figure(5), plot(t, servo, 'r-', t, combo4, 'b-');
legend('servo', 'combination');
ylabel('angle');
xlabel('time');

