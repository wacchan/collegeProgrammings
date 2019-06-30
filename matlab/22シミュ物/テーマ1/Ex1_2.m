len = length(b)+1;
D = zeros(len, len);
D(1,1) = s;
D(1,2:len) = b;
D(2:len, 1) = c;
D(2:len, 2:len) = A;
disp(D);
 