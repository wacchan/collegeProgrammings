function xout = xdot(t,x,k,l,ma,mb)
xadot1 = x(2);
xadot2 = k*(x(3)-x(1)-l)/ma;
xbdot1 = x(4);
xbdot2 = -k*(x(3)-x(1)-l)/mb;
xout = [xadot1; xadot2; xbdot1; xbdot2];