%
close all; clear all;

% serial object (we have to change the COM and BaudRate
s = serialport("COM17",9600, 115200);
% open serial port
fopen(s);
% Plotting data
i = 1;
while(1)
   data(i) = str2double(fscanf(s));
   
   plot(data);
   
   % our lidar reads up tp 40 meters
    ylim([0 40]);
   
   pause(0.01);
   i = i + 1;
    
end

