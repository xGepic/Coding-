var kartenarray = new Array(16);
var clicked = 0;
var secs = 0;
var gefunden = 0;
var versuche = 1;
var offen = 0;

function spielername(){
    var name = prompt("Bitte geben Sie Ihren Namen ein!");
    var userlabel = document.getElementById("userlabel");
    userlabel.innerHTML = name;
    timer();
	erstelleKarten();
}

function erstelleKarten() {
	for(var i = 0; i < 16; i++){
	var newDiv = document.createElement("div");
	var id = i+1;
	newDiv.setAttribute("id", id);
	newDiv.setAttribute("class", "karte");
	newDiv.setAttribute("onClick", "vergleichePaare(" + id + ")");
	kartenarray[i] = newDiv;
}
	shuffle(kartenarray);	
	var spielbereich = document.getElementById("spielbereich")
	for(var i = 0; i < 16; i++){
        if (i % 4 == 0){
            kartenarray[i].style.clear = "left";
		}
		spielbereich.appendChild(kartenarray[i]);
  }
}

function shuffle(kartenarray) {
var i, j, k;
  for (i = kartenarray.length -1; i > 0; i--) {
    j = Math.floor(Math.random() * i)
    k = kartenarray[i]
    kartenarray[i] = kartenarray[j]
    kartenarray[j] = k
  }
}

function timer(){
	if(gefunden < 8){
		secs++;	
		document.getElementById('zeitlabel').innerHTML = secs;
		window.setTimeout("timer()",1000);
	}
}

function vergleichePaare(x){
if (offen<2) {
	document.getElementById('versuchelabel').innerHTML = versuche;
		if(clicked == 0){
			clicked = x;
			offen = 1;			
		} else {		
			versuche++;
		    offen = 2;
			if((clicked + x) == 17){
				gefunden++;	
				window.setTimeout('fertigeKarte('+x+')',500);
			}else{	
				window.setTimeout('verdeckeKarte('+x+')',500);
			}
		}
	document.getElementById(x).style.backgroundImage = "url(pics/card" + x + ".png)";	
   }	
}

function verdeckeKarte(x){
	document.getElementById(clicked).style.backgroundImage = "url(pics/memoryBg.png)";
	document.getElementById(x).style.backgroundImage = "url(pics/memoryBg.png)";
	clicked = 0;	
	offen = 0;
}

function fertigeKarte(x){
	document.getElementById(clicked).setAttribute("onClick","");
	document.getElementById(clicked).style.backgroundImage = "url(pics/memoryBgI.png)";	
	document.getElementById(x).setAttribute("onClick","");
	document.getElementById(x).style.backgroundImage = "url(pics/memoryBgI.png)";	
	clicked = 0;	
	offen = 0;
}
