var arg = 0.;
var sinTimer = Date.now();

function MakeLed(red,green,blue){
	return {
		red: red,
		green: green,
		blue: blue
	};
}

function MultipleLed(led, val)
{
	return {
		red: constrain(led.red * val, 0, 255),
		green: constrain(led.green * val, 0, 255),
		blue: constrain(led.blue * val, 0, 255)
	};
}

function AddLed(led, val)
{
	return {
		red: constrain(led.red + val, 0, 255),
		green: constrain(led.green + val, 0, 255),
		blue: constrain(led.blue + val, 0, 255)
	};
}
function AddLedBefore(led, val, max)
{
	return {
		red: constrain(led.red + val, 0, max),
		green: constrain(led.green + val, 0, max),
		blue: constrain(led.blue + val, 0, max)
	};
}

function MiddleOfLed(led)
{
	return (led.red + led.green + led.blue) / 3;
}

function rgb(r, g, b){
  return "rgb("+r+","+g+","+b+")";
}

function ClearLeds()
{
	for(var i = 0; i < NUMLEDS; i++)
	{
		leds[i] = MakeLed(0,0,0);
	}
}

function InitLedsByColor(r,g,b)
{
	for(var i = 0; i < NUMLEDS; i++)
  	{
    	leds[i] = MakeLed(r,g,b);
  	}
}

function BeatLeds(beat)
{
	var bright = beatSin(5, 0.005, 0, 0, beat);
	for(var i = 0; i < NUMLEDS; i++)
	{
		if(MiddleOfLed(leds[i]) < 20)
			leds[i] = MakeLed(bright,bright,bright);
	}
}

function rgb2hsv(led)
{
	var r,g,b;
	var max, min;
	var h, s, v;
	var chroma;

	r = led.red / 255;
	g = led.green / 255;
	b = led.blue / 255;

	max = Math.max(r,g,b);
	min = Math.min(r,g,b);

	chroma = max - min;

	v = max;

	if(chroma == 0)
	{
		h = 0;
		s = 0;
		//v = max;
	}
	else
	{
		switch(v)
		{
			case r: h = 60 * (0 + (g-b)/chroma); break;
			case g: h = 60 * (2 + (b-r)/chroma); break;
			case b: h = 60 * (4 + (r-g)/chroma); break;
		}

		if(v > 0)
		{
			s = chroma / v;
		}
		else
		{
			s = 0;
		}
	}
	
	if(h < 0)
	{
		h = 360 + h;
	}

	return {
		hue: h,
		sat: s,
		val: v
	};
}

function hsv2rgb(led)
{
	var r,g,b;
	var h, s, v;
	//var i, f, p, q, t;
	var chroma, H, x, m;
	h = led.hue;
	s = led.sat;
	v = led.val;

	chroma = v * s;
	H = (h/60)%6;
	x = chroma * (1 - Math.abs((H%2) - 1));
	m = v - chroma;

	if(0 <= H && H < 1) {
    	r = chroma;
    	g = x;
    	b = 0;
  	} 
  	else if(1 <= H && H < 2) {
    	r = x;
    	g = chroma;
    	b = 0;
  	}
  	else if(2 <= H && H < 3) {
    	r = 0;
    	g = chroma;
    	b = x;
  	} 
  	else if(3 <= H && H < 4) {
    	r = 0;
    	g = x;
    	b = chroma;
  	} 
  	else if(4 <= H && H < 5) {
    	r = x;
    	g = 0;
    	b = chroma;
  	} 
  	else if(5 <= H && H < 6) {
    	r = chroma;
    	g = 0;
    	b = x;
  	} 
  	else {
    	r = 0;
    	g = 0;
    	b = 0;
  	}
  
  	r = parseInt((r+m)*255);
  	g = parseInt((g+m)*255);
  	b = parseInt((b+m)*255);
	/*
	i = parseInt(h*6);
	f = h * 6 - i;
	p = v * (1 - s);
	q = v * (1 - f * s);
	t = v * (1 - (1 - f) * s);

	switch (i%6) {
		case 0: {	r = v;	g = t;	b = p;	break; }
		case 1: {	r = q; 	g = v; 	b = p; 	break; }
		case 2: {	r = p; 	g = v; 	b = t; 	break; }
		case 3: {	r = p;	g = q;	b = v; 	break; }
		case 4: {	r = t;  g = p;  b = v;  break; }
		case 5: {	r = v;  g = p;  b = q;	break; }
	}

	r = parseInt(r * 255);
	g = parseInt(g * 255);
	b = parseInt(b * 255);
	*/
	return {
		red: r,
		green: g,
		blue: b
	};
}
function fadeToBlackByHSV(fadeStep)
{
	var hsvLed;

	for(var i = 0; i < NUMLEDS; i++)
	{
		hsvLed = rgb2hsv(leds[i]);

		hsvLed.val = constrain(hsvLed.val - fadeStep, 0, 1);

		leds[i] = hsv2rgb(hsvLed);
	}
}
function fadeToBlack(fadeStep)
{
	var r,g,b;
	for(var i = 0; i < NUMLEDS; i++)
	{
		r = leds[i].red;
		g = leds[i].green;
		b = leds[i].blue;

		r = constrain(r-fadeStep, 0, 255);
		g = constrain(g-fadeStep, 0, 255);
		b = constrain(b-fadeStep, 0, 255);

		leds[i] = MakeLed(r,g,b);
	}
}
function fadeToBlackSaveColor(fadeStep)
{
	var r,g,b;
	var rStep, gStep, bStep;
	var min;
	for(var i = 0; i < NUMLEDS; i++)
	{
		r = leds[i].red;
		g = leds[i].green;
		b = leds[i].blue;

		min = Math.min(r,g,b);
		if(min == 0) min = 1;
		rStep = parseInt(leds[i].red / min);
		gStep = parseInt(leds[i].green / min);
		bStep = parseInt(leds[i].blue / min);

		r = constrain(r - (rStep * fadeStep), 0, 255);
		g = constrain(g - (gStep * fadeStep), 0, 255);
		b = constrain(b - (bStep * fadeStep), 0 ,255);

		leds[i] = MakeLed(r,g,b);
	}
}
function constrain(val, min, max)
{
	if(val <= min)
		return min;
	else if (val >= max)
		return max;
	else
		return val;
}

function beatSin(amplitude, argStep, phase, timeStep, module)
{
	if(Date.now() - sinTimer > 20)
	{
		sinTimer = Date.now();
		arg = constrain(arg + argStep, 0, 2 * Math.PI);
	}

	if(arg == 2 * Math.PI)
		arg = 0;

	return amplitude * (Math.sin((arg + phase)*module)+1);
}

function randomInt(min, max) {
	return min + Math.floor((max - min) * Math.random());
}

function randValWithProb(min, max, prob)
{
	var val = 0;
	if(randomInt(0,100) > prob)
	{
		val = randomInt(min,max);
	}
	else
	{
		val = 0;
	}
	return val;
}