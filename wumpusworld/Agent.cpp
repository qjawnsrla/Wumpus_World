#include "Agent.h"

Agent::Agent() {

}
	void Agent::goForward() {
		shot = false;
		
	}
	void Agent::goForwardWithoutStacking() {
		shot = false;

	}
	void Agent::turnLeft() {
		shot = false;

	}
	void Agent::turnRight() {
		shot = false;

	}
	void Agent::climb() {

	}
	void Agent::grab() {
		havingGold = true;
	}
	void Agent::die() {

	}
	void Agent::setGrid(int x, int y, int state, bool t) {

	}
	void Agent::goBackward() {

	}
	bool Agent::isGrid(int x, int y, int state) {

	}
	int Agent::reasoning(bool stench, bool breeze, bool glitter, bool bump) {
		if (bump == true) {
			//���� ��ġ�� ƨ���� ����
			setGrid(posX, posY, wall, true);
			goBackward();
			return 0;
		}
		visited[posX][posY] = true;
		setGrid(posX, posY, safe, true);
		if (!stench && !breeze) {
			//�ƹ� �ϵ� ������ ��� ����
			setGrid(frontPosX, frontPosY, safe, true);
			setGrid(leftPosX, leftPosY, safe, true);
			setGrid(rightPosX, rightPosY, safe, true);
			setGrid(backPosX, backPosY, safe, true);
		}
		if (stk.empty() && havingGold) {
			//���� �ְ� 1,1�� ����
			climb();
			return 3;
		}
		if (havingGold) {
			// ���� �ְ� ���� 1,1�� �������� ����
			if (frontPosX != stk.top().first || frontPosY != stk.top().second) {
				//�Դ� Ÿ���� �ٶ󺸰� ���� ���� ���
				turnRight();
				return 0;
			}
			else {
				goForwardWithoutStacking();
				return 0;
			}
		}
		if (glitter == true) {
			grab();
			return 2;
		}
		// �湮���� �ʰ� ���� �ƴ� ������ Ÿ�Ϸ� �̵�
		if (visited[frontPosX][frontPosY] == false && isGrid(frontPosX, frontPosY, safe) == true && isGrid(frontPosX, frontPosY, wall) == false) {
			goForward();
			return 0;
		}
		else if (visited[rightPosX][rightPosY] == false && isGrid(rightPosX, rightPosY, safe) == true && isGrid(rightPosX, rightPosY, wall) == false) {
			turnRight();
			return 0;
		}
		else if (visited[leftPosX][leftPosY] == false && isGrid(leftPosX, leftPosY, safe) == true && isGrid(leftPosX, leftPosY, wall) == false) {
			turnLeft();
			return 0;
		}
		else if (visited[backPosX][backPosY] == false && isGrid(backPosX, backPosY, safe) == true && isGrid(backPosX, backPosY, wall) == false) {
			turnRight();
			return 0;
		}

		if (
			(isGrid(frontPosX, frontPosY, wall) == true || isGrid(frontPosX, frontPosY, pit) == true) &&
			(isGrid(backPosX, backPosY, wall) == true || isGrid(backPosX, backPosY, pit) == true) &&
			(isGrid(leftPosX, leftPosY, wall) == true || isGrid(leftPosX, leftPosY, pit) == true) &&
			(isGrid(rightPosX, rightPosY, wall) == true || isGrid(rightPosX, rightPosY, pit) == true)
			) {
			//����� �� �� ���� ���
			return 3;
		}

		if (visited[frontPosX][frontPosY] == true) {
			//���� �湮�� Ÿ���� ���
			if (
				(isGrid(backPosX, backPosY, wall) == true || isGrid(backPosX, backPosY, pit) == true || visited[backPosX][backPosY]==true) &&
				(isGrid(leftPosX, leftPosY, wall) == true || isGrid(leftPosX,leftPosY,pit) == true|| visited[leftPosX][leftPosY]==true) &&
				(isGrid(rightPosX, rightPosY, wall) == true || isGrid(rightPosX,rightPosY,pit)==true|| visited[rightPosX][rightPosY]==true)
				) {
				//��, ��, �� �湮�Ұ�(Pit �Ǵ� �� �Ǵ� �湮��)
				if (frontPosX != stk.top().first || frontPosY != stk.top().second) {
					//�Դ� Ÿ���� �ٶ󺸰� ���� ���� ���
					turnRight();
					return 0;
				}
				else {
					setGrid(posX, posX, wall, true);
					goForwardWithoutStacking();
					stk.pop();
					return 0;
				}
			}
			else {
				turnRight();
				return 0;
			}
		}
		if (isGrid(frontPosX, frontPosY, wall) == true) {
			//���� ���� ���
			turnRight();
			return 0;
		}
		if (stench == true || isGrid(frontPosX, frontPosY, wumpus) == true) {
			//7.�������ų� �տ� ������ �ִ� ���
			if (shot == true) {
				//�̹� ������
				goForward();
				return 0;
			}
			else {
				if (arrows > 0) {
					shot = true;
					return 1;
				}
				else {
					goForward();
					return 0;
				}
			}
		}
		if (isGrid(frontPosX, frontPosY, pit) == true) {
			//��Ÿ�Ͽ� ������
			turnRight();
			return 0;
		}
		if (breeze == true) {
			//�ٶ��� ������
			goForward();
			return 0;
		}
		goForward();
		return 0;
	}
