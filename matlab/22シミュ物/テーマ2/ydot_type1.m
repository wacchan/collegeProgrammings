function yout = ydot_type1(t, y, mu)
    ydot1 = y(2);
    ydot2 = mu*(1-(y(1))^2)*y(2)-y(1);
    yout = [ydot1; ydot2];