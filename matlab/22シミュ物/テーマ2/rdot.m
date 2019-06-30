function rout = rdot(t,r, gm)
rdot1 = r(2);
rdot2 = r(1) * (r(4))^2 - gm/(r(1))^2;
thetadot1 = r(4);
thetadot2 = -(2*r(2)*r(4))/r(1);
rout = [rdot1; rdot2; thetadot1; thetadot2];