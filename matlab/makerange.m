
% Read in the scan data
%
A = csvread('cutecom.csv');

% Convert the angular measurements to x/y/z
%
theta = A(:,1) * pi / 180;
phi   = A(:,2) * pi / 180;
R     = A(:,3);

% The pan tilt bracket is modeled as a translation, rotation, translation,
% rotation to move to the ray/origin of the ping sensor
%
t1 = createTranslation3d(0, 6.98500, 0);
t2 = createTranslation3d(0, 3.17500, 0);
t3 = createTranslation3d(0, 5.71500, 0);
r1 = eye(4,4); 
r2 = eye(4,4);

% Convert each point from a spherical to a cartesian coordinate system
%
for i = 1:length(theta)
    
    r1 = createRotationOy(theta(i));
    r2 = createRotationOx(phi(i));
   
    r2(1,1) = cos(theta(i)); r2(1,2) = -sin(theta(i)); 
    r2(2,1) = sin(theta(i)); r2(2,2) =  cos(theta(i)); 
  
    T = t3 * r2 * t2 * r1 * t1;
    
    p = T * [0, 0, 0, 1]';
    v = T * [0, 1, 0, 0]';
    
    x(i) = p(1) + v(1) * R(i);
    y(i) = p(2) + v(2) * R(i);
    z(i) = p(3) + v(3) * R(i);
end

x = R .* cos(theta) .* sin(phi);
y = R .* sin(theta) .* sin(phi);
z = R .* cos(phi);

% Plot the x/y/z locations
%
plot3(x, y, z, '.');

B(:,1) = x;
B(:,2) = y;
B(:,3) = z;
save('B.asc', 'B', '-ASCII');

img = zeros(150, 150);
idx = sub2ind(size(img), int32(A(:,2)), int32(A(:,1)));
img(idx) = A(:,3);
img2 = min(50, img);
figure(2), imagesc(flipud(img2)), impixelinfo;
