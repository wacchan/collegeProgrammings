import java.util.Scanner; 
 
class FillRegion{
    public final static int BACK   = 0;  // ”wŒi‰æ‘f’l     
    public final static int BORDER = 1;  // ‹«ŠE‰æ‘f’l     
    public final static int REGION = 2;  // —Ìˆæ‰æ‘f’l 
 
    static int target;        // ’–Ú‰æ‘f’l     
    static int width,height;  // ‰æ‘œƒTƒCƒY 

    static int[][] dot = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},  
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  
        {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0},  
        {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},  
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},  
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},  
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},  
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},  
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},  
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},  
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},  
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},  
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},  
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},}; 

    static void fill(int x, int y){
        x = x % 16; y = y % 16;
        dot[x][y] = REGION;  
        if(y>0)if(dot[x][y-1] == target)  fill(x, y-1);  
        if(x<15)if(dot[x+1][y] == target)  fill(x+1, y);  
        if(y<15)if(dot[x][y+1] == target)  fill(x, y+1);  
        if(x>0)if(dot[x-1][y] == target)  fill(x-1, y);     
    } 
 
    static void show(){  
        System.out.println(width + " x " + height);  
        System.out.print("   ");  
        for(int y=0; y<height; y++){      
            System.out.printf("%2d", y);  
        }  
        System.out.println();  
        for(int x=0; x<width; x++){      
            System.out.printf("%2d ", x);      
            for(int y=0; y<height; y++){   
                switch (dot[x][y]){   
                    case BACK:       
                    System.out.print("  ");       
                    break;   
                    case BORDER:       
                    System.out.print(" ¡");       
                    break;   case REGION:       
                    System.out.print(" *");       
                    break;   
                }      
            }      
            System.out.println();  
        }  
        System.out.println();     
    } 

    public static void main(String[] args){
        width  = dot.length;  height = dot[0].length; 
        show();  // •\Ž¦i“h‚è‚Â‚Ô‚µ‘Oj 
        target = dot[8][8]; 
        fill(5, 8); 
        show();  // •\Ž¦i“h‚è‚Â‚Ô‚µŒãj    
    }
}

  