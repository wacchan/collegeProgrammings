import java.io.*;

class StringStack{
  private int max;
  private int ptr;
  private String[] stk;
  private int count;

  public class EmptyStringStackException extends RuntimeException{
    public EmptyStringStackException() { }
  }

  public class OverflowStringStackException extends RuntimeException{
    public OverflowStringStackException() { }
  }

  public StringStack(int capacity){
    ptr = 0;
    max = capacity;
    try{
      stk = new String[max];
    }
    catch(OutOfMemoryError e){
      max = 0;
    }
  }

  public int size(){
    return ptr;
  }

  public int capacity(){
    return max;
  }

  public void push(String x) throws OverflowStringStackException{
    if(ptr >= max){
      throw new OverflowStringStackException();
    }
    stk[ptr] = x;
    ptr++;
    count++;
  }

  public String pop() throws EmptyStringStackException{
    if(ptr <= 0){
      throw new EmptyStringStackException();
    }
    ptr--;
    count--;
    return stk[ptr];
    
  }

  public String peek() throws EmptyStringStackException{
    if(ptr <= 0){
      throw new EmptyStringStackException();
    }
    return stk[ptr-1];
  }

  public void dump(){
    if(ptr <= 0){
      System.out.println("スタックは空です。");
    }
    else{
      for(int i=0; i < count; i++){
        System.out.print(stk[i] + " ");
      }
      System.out.println();
    }
  }
}

class StringLinkedList{

  class Node{
    private String data;
    private Node next;
  
    Node(String data, Node next){
      this.data = data;
      this.next = next;
    }
  }

  private Node head;
  private Node crnt;

  public StringLinkedList(){
    head = crnt = null;
  }

  public void addFirst(String obj){
    Node ptr = head;
    head = crnt = new Node(obj, ptr);
  }

  public void addLast(String obj){
    if(head == null)
      addFirst(obj);
    else{
      Node ptr = head;
      while(ptr.next != null)
        ptr = ptr.next;
      ptr.next = crnt = new Node(obj, null);
    }
  }

  public void removeFirst(){
    if(head != null)
      head = crnt = head.next;
  }

  public void removeLast(){
    if(head != null){
      if(head.next == null)
        removeFirst();
      else{
        Node ptr = head;
        Node pre = head;

        while(ptr.next != null){
          pre = ptr;
          ptr = ptr.next;
        }
        pre.next = null;
        crnt = pre;
      }
    }
  }

  public void dump(){
    Node ptr = head;

    while(ptr != null){
      System.out.print(ptr.data + " ");
      ptr = ptr.next;
    }
    System.out.println();
  }

  public int size(){
    int num = 0;
    if(head != null){
      Node ptr = head;

      while(ptr.next != null){
        num++;
        ptr = ptr.next;
      }
      return num+1;
    }
    else{
      return num;
    }
  }

  public String getFirstNode(){
    String str = head.data;
    head = crnt = head.next;
    return str;
  }

  public String getLastNode(){
    Node ptr = head;
    Node pre = head;
    if(head.next == null)
      removeFirst();
    else{
      while(ptr.next != null){
        pre = ptr;
        ptr = ptr.next;
      }
      pre.next = null;
      crnt = pre;
    }
    return ptr.data;
  }
}

class InfixToRPN{

  static boolean isDigit(String s){
    try{
      Integer.parseInt(s);
      return true;
    }
    catch(NumberFormatException e){
      return false;
    }
  }

  static void infixToRPN(String[] infix, StringLinkedList RPN){
    StringStack stack = new StringStack(infix.length);
    int i = 0;

    for(int j=0; j < infix.length; j++){
      if(isDigit(infix[j])){
        System.out.println(j + ": " + infix[j] + " (digit)");
        RPN.addLast(infix[j]);
      }
      else{
        if(i == 0){
          System.out.println(j + ": " + infix[j] + " (operator)");
        }
        if(stack.size() == 0){
          stack.push(infix[j]);
          i = 0;
        }
        else{
          if(infix[j].equals("+") || infix[j].equals("-")){
            RPN.addLast(stack.pop());
            i = 1;
            j--;
          }
          else{
            stack.push(infix[j]);
            i = 0;
          }
        }
      }
    }
    
    if(stack.size() != 0){
      while(stack.size() != 0){
        RPN.addLast(stack.pop());
      }
    }
  }

  public static void main(String args[]) throws IOException{
    System.out.print("中置記法の数式 : ");

    BufferedReader br =
      new BufferedReader(new InputStreamReader(System.in));

    String targetInfix = br.readLine();
    String[] tokens = targetInfix.split(" ");
    System.out.println("targetInfix = " + targetInfix);

    StringLinkedList RPN = new StringLinkedList();

    infixToRPN(tokens, RPN);

    System.out.println();
    RPN.dump();
  }
}
