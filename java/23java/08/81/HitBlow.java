import java.util.Scanner;



public class HitBlow{

    public static void main(String[] args){

	Scanner scan = new Scanner(System.in);



	int[] answer = new int[4];

	int[] user = new int[4];



	// ������3�������̐���

	int[] array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int remainder = 10;

	for(int i=0; i<4; i++){

	    int select = (int)(Math.random() * remainder);

	    answer[i] = array[select];

	    array[select] = array[remainder-1];

	    remainder--;

	}



	// ���[�U���͉�

	int count = 1;



	// ���[�v

	while(true){

	    // ���[�U��3����������

	    System.out.print("4�������̓��́F");

	    String input = scan.nextLine();



	    // ���̓G���[�̃t���O

	    boolean error = false;



	    // ���̓f�[�^��3�������m�F

	    //---------- ����������1�i��������j ----------//

	    int length = input.length();

	    if(length != 4){
			error = true;
		}



	    //---------- ����������1�i�����܂Łj ----------//

		

	    if(error){

		System.out.println("ERROR : 4���œ��͂��ĉ������B");

		System.out.println();



		continue;

	    }



	    // ���̓f�[�^�����l���m�F

	    //---------- ����������2�i��������j ----------//

	    for(int i=0; i<length; i++){

			char c = input.charAt(i);

			if(c < '0' || '9' < c){
				error = true;
			}

	    }

	    //---------- ����������2�i�����܂Łj ----------//



	    if(error){

		System.out.println("ERROR : ���l����͂��ĉ������B");

		System.out.println();



		continue;

	    }



	    // ���͂������l�ɏd�����������m�F

	    //---------- ����������3�i��������j ----------//

	    for(int i=0; i<length-1; i++){

			for(int j= i+1; j<length; j++){

		    	if(input.charAt(i) == input.charAt(j)){
					error = true;
				}

			}

	    }

	    //---------- ����������3�i�����܂Łj ----------//



	    if(error){

		System.out.println("ERROR : �d�����Ȃ��悤�ɓ��͂��ĉ������B");

		System.out.println();



		continue;

	    }



	    for(int i=0; i<length; i++){

		user[i] = Integer.parseInt(input.substring(i, i+1));

	    }



	    // �q�b�g����

	    //---------- ����������4�i��������j ----------//

	    int hit = 0;

	    for(int i=0; i<length; i++){

			if(user[i] == answer[i]){
				hit++;
			}

		    

	    }

	    //---------- ����������4�i�����܂Łj ----------//



	    // �u���[����

	    //---------- ����������5�i��������j ----------//

	    int blow = 0;

	    for(int i=0; i<length; i++){

			for(int j=0; j<length; j++){

		    	if(user[i] == answer[j]){
					blow++;
				}



			}

	    }

	    //---------- ����������5�i�����܂Łj ----------//



	    // ����

		if(hit == length){

		System.out.println("�����B" + count + "��ڂŐ����B");

		break;

	    }

	    else{

		System.out.println("Hit " + hit + "��, Blow " + (blow-hit) + "��");

		System.out.println();

		count++;

	    }

	}

    }

}

