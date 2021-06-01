%
close all; clear all;

% serial object (we have to change the COM and BaudRate
Dragon = serialport('COM6',9600);


% initialize x values
x = str2num(readline(Dragon));
y = str2num(readline(Dragon));
 
data = zeros(x,y);


% Plotting data
for i = 1:1:x
    for j = 1:1:y
        data(i,j)=str2num(readline(Dragon));
        if i < 5 
            plot(i,j,'k*')  % Danger zone between 0 - 5 m
            hold on
        elseif i == 5.01:7 
            plot(i,j,'b*')  
            hold on
        elseif i == 7.01:10 
            plot(i,j,'g*')  
            hold on
        elseif i == 10.001:20 
            plot(i,j,'r*')  
            hold on
        elseif i == 20:40 
            plot(i,j,'y*')  % Far range
            hold on
        end
    hold on
    grid on
    end
end