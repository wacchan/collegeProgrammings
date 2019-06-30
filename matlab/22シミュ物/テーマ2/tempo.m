function tout = tempo(z,h)
zlmax1 = ilocalmax(z);
zfind = find(zlmax1);
ztemp1 = abs(zfind(2)-zfind(3))/h;
tout = round(ztemp1, 3,'significant');