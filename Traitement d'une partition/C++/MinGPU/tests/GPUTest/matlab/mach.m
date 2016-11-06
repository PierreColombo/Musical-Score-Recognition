  % mach filter test
  close all;
  profile on;
  j = 0;
  for i = -9: 3: 9
      
    buf = sprintf('c:\\image\\t%d.pgm', i);
    h = imread(buf);
    im = imread('c:\image\clip4.pgm');
    imshow(im);
    width = 77;
    threshold = 0.43;
    
    [rows, cols] = size(im);
    cc = abs(normxcorr2(h, im));
    figure; imagesc(cc); colormap(gray(256));
    [max_cc, imax] = max(cc(:));
    max_cc
    [ypeak, xpeak] = ind2sub(size(cc),imax(1))
    %imagesc(cc);

    if max_cc > threshold
        hold on
        [xpeak-width, ypeak-width, width, width]
        rectangle('Position', [xpeak-width, ypeak-width, width, width], 'EdgeColor', 'b', 'LineWidth', 2);
        hold off
    end
  end
  profile viewer;
  
    
