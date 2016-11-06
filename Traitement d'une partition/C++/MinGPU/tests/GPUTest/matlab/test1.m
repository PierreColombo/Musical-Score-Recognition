% generate optical flow grid from U, V files

close all;
u = imread('c:\image\U10.pgm');
v = imread('c:\image\V10.pgm');

[x,y] = meshgrid(1:1:192, 1:1:116);
%SUBPLOT(2,1,2); colormap(gray)

figure; colormap(gray(256)); quiver(x, -y, u, v); 
axis equal, axis off

F = rgb2gray(frame2im(getframe(gcf)));
imwrite(F, 'c:\image\op10.bmp', 'BMP');



