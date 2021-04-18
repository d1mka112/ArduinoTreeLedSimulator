let start = Date.now();
let timePassed = Date.now() - start;
let timer;

let timeAnimation = 100000;

let NUMLEDS = 600;

var leds = [];


function Start()
{       
  timer = setInterval(StartAnimation, 20);

  InitLedsByColor(0,0,0);
  //InitLedsByColor(100,100,200);
}

function Draw()
{
  let start = 10;
  let size = 3;

  var k;

  var led = {red: 0, green: 0, blue: 0};

  var canvas = document.getElementById("canvas");
  var ctx = canvas.getContext("2d");

  ctx.fillStyle = rgb(0,0,0);
  ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);

  for(var i = 0; i < NUMLEDS; i++)
  {
    led = MultipleLed(leds[i], 3);
    ctx.fillStyle = rgb(led.red, led.green, led.blue);
    ctx.fillRect(start + i * size, 10, size, size);
  }

  var x = 0;
  var c = 0.1;
  for(var i = 0; i < NUMLEDS; i++)
  {
    k = i/(NUMLEDS-1);
    k = k * 7;

    if(Derivative(k) >= 0)
    {
      led = MultipleLed(leds[i], 3);
    }
    else
    {
      led = MultipleLed(leds[i], 0.3);
    }
    //led = MultipleLed(leds[i], 3);

    ctx.fillStyle = rgb(led.red, led.green, led.blue);
     
    //x += Math.pow(c,2) / (Math.pow(Derivative(x),2) + 1);

    //ctx.fillRect(200 + TreeFunction(x)*30, 700 - x*1000, size, size);
    ctx.fillRect(200 + TreeFunction(k)*30, 700 - i, size, size);
  }

}

function TreeFunction(x)
{
  return TreeLine(x) * Math.sin(2 * Math.PI * x);
}

function TreeLine(x)
{
  return (-5./7.)* x + 5;
}

function Derivative(x)
{
  return ((-5./7.) * Math.sin(2 * Math.PI * x)) + (2 * Math.PI * Math.cos(2 * Math.PI * x) * ((-5./7. * x) + 5));
}

function Parabolic(x)
{
  return (1./10.) * x * x;
}

function StartAnimation()
{
  timePassed = Date.now() - start;
  if(timePassed >= timeAnimation)
  {
    clearInterval(timer);
    return;
  }

  //fadeToBlack(10);
  //moveDots();
  //movingDots();
  //movingDots2();
  fillStrip();
  //Strobo();
  //BeatLeds(5);
  Draw();
}


