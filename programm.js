var view = 0;
var pos = 0;
var speed = 1;

function moveDots() {
	ClearLeds();

	for(var i = 0; i < NUMLEDS - view; i++)
	{
		if(i%10 == 0)
			leds[i+view] = MakeLed(30,30,150);
	}

	view = constrain(view - 1, 0, 10);

	if(view == 0)
		view = 10;
}



function movingDots2()
{
	var add;

	pos = parseInt(beatSin((NUMLEDS-1)/2, 0.005, 0, 0, 1));

	add = randValWithProb(50,100, 70);
	leds[pos] = MakeLed(50 + add, 100 + add, 20 + add);

	add = randValWithProb(50,100, 70);
	leds[NUMLEDS-1-pos] = MakeLed(100 + add, 20 + add, 50 + add);

	pos = parseInt(beatSin((NUMLEDS-1)/2, 0.005, Math.PI/2, 0, 1));

	add = randValWithProb(50,100, 70);
	leds[pos] = MakeLed(50 + add, 10 + add, 100 + add);

	add = randValWithProb(50,100, 70);
	leds[NUMLEDS-1-pos] = MakeLed(100 + add,70 + add,10 + add);
	
	//BeatLeds(10);
	//fadeToBlackSaveColor(1);
	fadeToBlackByHSV(0.005);
	//fadeToBlack(1);
	console.log(pos);
	console.log(leds[1]);
}

function Strobo()
{
	for(var i = 0; i < NUMLEDS; i++)
	{
		leds[i] = MakeLed(30,10,20);
	}
	pos = randomInt(0,100);
	if(pos > 10)
	{
		pos = randomInt(0, NUMLEDS-1);

		leds[pos] = MakeLed(255,255,255);
	}	
	fadeToBlack(10);
}

function fillStrip()
{
	speed = speed + 0.01;
	pos = constrain(pos + 1, 0, NUMLEDS-1);
	
	if(pos == NUMLEDS-1)
	{/*
		for(var i = 1; i < 15; i++)
		{
			leds[NUMLEDS - i] = MakeLed(255, 255, 255);
		}*/
		pos = 0;
		speed = 1;
	}

	leds[NUMLEDS-1-pos] = MakeLed(50, 20, 100);

	if(randomInt(0, 100) > 65)
	{
		leds[NUMLEDS-1-pos] = MakeLed(200, 25, 155);
	}
/*
	for(var i = 0; i < NUMLEDS-1; i++)
	{
		if(i <= pos)
		{
			leds[i] = MakeLed(50, 100, 20);
		}
		else
		{
			leds[i] = MakeLed(0,0,0);
		}
	}*/
	
	//fadeToBlackSaveColor(1);
	fadeToBlackByHSV(0.005);
	//fadeToBlack(1);
}

function movingDots()
{
	//fadeToBlack(30);
	fadeToBlackSaveColor(5);
	for(var i = 0; i < NUMLEDS - view; i++)
	{
		if(i%10 == 0)
		{
			if(i <= pos)
			{
				leds[i + view] = MakeLed(200, 100,40);
			}
			else
			{
				leds[i + view] = MakeLed(100, 40, 200);
			}
		}
	}

	view = constrain(view - 1, 0, 10);

	if(view == 0)
		view = 10;

	pos = constrain(pos - 1, 0, NUMLEDS-1);

	if(pos == 0)
		pos = NUMLEDS-1;
}