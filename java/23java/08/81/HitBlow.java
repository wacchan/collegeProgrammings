import java.util.Scanner;



public class HitBlow{

    public static void main(String[] args){

	Scanner scan = new Scanner(System.in);



	int[] answer = new int[4];

	int[] user = new int[4];



	// 答えの3桁数字の生成

	int[] array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int remainder = 10;

	for(int i=0; i<4; i++){

	    int select = (int)(Math.random() * remainder);

	    answer[i] = array[select];

	    array[select] = array[remainder-1];

	    remainder--;

	}



	// ユーザ入力回数

	int count = 1;



	// ループ

	while(true){

	    // ユーザの3桁数字入力

	    System.out.print("4桁数字の入力：");

	    String input = scan.nextLine();



	    // 入力エラーのフラグ

	    boolean error = false;



	    // 入力データが3文字か確認

	    //---------- 未実装部分1（ここから） ----------//

	    int length = input.length();

	    if(length != 4){
			error = true;
		}



	    //---------- 未実装部分1（ここまで） ----------//

		

	    if(error){

		System.out.println("ERROR : 4桁で入力して下さい。");

		System.out.println();



		continue;

	    }



	    // 入力データが数値か確認

	    //---------- 未実装部分2（ここから） ----------//

	    for(int i=0; i<length; i++){

			char c = input.charAt(i);

			if(c < '0' || '9' < c){
				error = true;
			}

	    }

	    //---------- 未実装部分2（ここまで） ----------//



	    if(error){

		System.out.println("ERROR : 数値を入力して下さい。");

		System.out.println();



		continue;

	    }



	    // 入力した数値に重複が無いか確認

	    //---------- 未実装部分3（ここから） ----------//

	    for(int i=0; i<length-1; i++){

			for(int j= i+1; j<length; j++){

		    	if(input.charAt(i) == input.charAt(j)){
					error = true;
				}

			}

	    }

	    //---------- 未実装部分3（ここまで） ----------//



	    if(error){

		System.out.println("ERROR : 重複しないように入力して下さい。");

		System.out.println();



		continue;

	    }



	    for(int i=0; i<length; i++){

		user[i] = Integer.parseInt(input.substring(i, i+1));

	    }



	    // ヒット判定

	    //---------- 未実装部分4（ここから） ----------//

	    int hit = 0;

	    for(int i=0; i<length; i++){

			if(user[i] == answer[i]){
				hit++;
			}

		    

	    }

	    //---------- 未実装部分4（ここまで） ----------//



	    // ブロー判定

	    //---------- 未実装部分5（ここから） ----------//

	    int blow = 0;

	    for(int i=0; i<length; i++){

			for(int j=0; j<length; j++){

		    	if(user[i] == answer[j]){
					blow++;
				}



			}

	    }

	    //---------- 未実装部分5（ここまで） ----------//



	    // 結果

		if(hit == length){

		System.out.println("正解。" + count + "回目で成功。");

		break;

	    }

	    else{

		System.out.println("Hit " + hit + "個, Blow " + (blow-hit) + "個");

		System.out.println();

		count++;

	    }

	}

    }

}

