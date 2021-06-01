close all; clear all;

% serial object (we have to change the COM and BaudRate
Dragon = serialport('COM6',9600);


% initialize x values
x = str2num(readline(Dragon));
y = str2num(readline(Dragon));
 
data = zeros(x,y);


% Plotting data
for i = 1:1:x
    if mod(x,2)==0
        for j = 1:1:y
            data(i,j)=str2num(readline(Dragon));
        end
    else
        for j = y:-1:1
            data(i,j)=str2num(readline(Dragon));
        end
    end
end

imagesc(data)