class Number {
    protected int num;

    public Number(int n) {
        num = n;
    }

    public String toString() {
        return null;
    }
}

class BinaryNumber extends Number {
    public BinaryNumber(int n) {
        super(n);
    }

    public String toString() {
        return Integer.toBinaryString(num);
    }
}

class OctalNumber extends Number {
    public OctalNumber(int n) {
        super(n);
    }

    public String toString() {
        return Integer.toOctalString(num);
    }
}

class DecimalNumber extends Number {
    public DecimalNumber(int n) {
        super(n);
    }

    public String toString() {
        return String.valueOf(num);
    }
}

class HexNumber extends Number {
    public HexNumber(int n) {
        super(n);
    }

    public String toString() {
        return Integer.toHexString(num);
    }
}

class NumberTester {
    public static void main(String[] args) {
        DecimalNumber n10 = new DecimalNumber(12);
        BinaryNumber n2 = new BinaryNumber(12);
        OctalNumber n8 = new OctalNumber(12);
        HexNumber n16 = new HexNumber(12);

        System.out.println("10 進数; " + n10);
        System.out.println(" 2 進数: " + n2);
        System.out.println(" 8 進数: " + n8);
        System.out.println("16 進数: " + n16);
    }
}