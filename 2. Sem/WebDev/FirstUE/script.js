function adition(){
    var nummer_1 = parseFloat(document.getElementById("nummer1").value);
    var nummer_2 = parseFloat(document.getElementById("nummer2").value);

    document.getElementById("ergebnis").innerHTML= nummer_1+nummer_2;

     let element = document.getElementById("darstellungsort");
     let z1 = document.createElement("p");
     let b2 = document.createElement("p");
     let z3 = document.createElement("p");
     let b4 = document.createElement("p");
     let z5 = document.createElement("p");

     z1.innerHTML = parseFloat(document.getElementById("nummer1").value);
     b2 = document.createTextNode("+");
     z3.innerHTML = parseFloat(document.getElementById("nummer2").value);
     b4 = document.createTextNode("=");
     z5.innerHTML = parseFloat(document.getElementById("nummer1").value)+parseFloat(document.getElementById("nummer2").value);


     element.appendChild(z1);
     element.appendChild(b2);
     element.appendChild(z3);
     element.appendChild(b4);
     element.appendChild(z5);
}

function subtraktion(){
    var nummer_1 = parseFloat(document.getElementById("nummer1").value);
    var nummer_2 = parseFloat(document.getElementById("nummer2").value);

    document.getElementById("ergebnis").innerHTML= nummer_1-nummer_2;

     let element = document.getElementById("darstellungsort");
     let z1 = document.createElement("p");
     let b2 = document.createElement("p");
     let z3 = document.createElement("p");
     let b4 = document.createElement("p");
     let z5 = document.createElement("p");

     z1.innerHTML = parseFloat(document.getElementById("nummer1").value);
     b2 = document.createTextNode("-");
     z3.innerHTML = parseFloat(document.getElementById("nummer2").value);
     b4 = document.createTextNode("=");
     z5.innerHTML = parseFloat(document.getElementById("nummer1").value)-parseFloat(document.getElementById("nummer2").value);


     element.appendChild(z1);
     element.appendChild(b2);
     element.appendChild(z3);
     element.appendChild(b4);
     element.appendChild(z5);
}

function multiplikation(){
    var nummer_1 = parseFloat(document.getElementById("nummer1").value);
    var nummer_2 = parseFloat(document.getElementById("nummer2").value);

    document.getElementById("ergebnis").innerHTML= nummer_1*nummer_2;

     let element = document.getElementById("darstellungsort");
     let z1 = document.createElement("p");
     let b2 = document.createElement("p");
     let z3 = document.createElement("p");
     let b4 = document.createElement("p");
     let z5 = document.createElement("p");

     z1.innerHTML = parseFloat(document.getElementById("nummer1").value);
     b2 = document.createTextNode("*");
     z3.innerHTML = parseFloat(document.getElementById("nummer2").value);
     b4 = document.createTextNode("=");
     z5.innerHTML = parseFloat(document.getElementById("nummer1").value)*parseFloat(document.getElementById("nummer2").value);


     element.appendChild(z1);
     element.appendChild(b2);
     element.appendChild(z3);
     element.appendChild(b4);
     element.appendChild(z5);
}

function division(){
    var nummer_1 = parseFloat(document.getElementById("nummer1").value);
    var nummer_2 = parseFloat(document.getElementById("nummer2").value);

    document.getElementById("ergebnis").innerHTML= nummer_1/nummer_2;

     let element = document.getElementById("darstellungsort");
     let z1 = document.createElement("p");
     let b2 = document.createElement("p");
     let z3 = document.createElement("p");
     let b4 = document.createElement("p");
     let z5 = document.createElement("p");

     z1.innerHTML = parseFloat(document.getElementById("nummer1").value);
     b2 = document.createTextNode("/");
     z3.innerHTML = parseFloat(document.getElementById("nummer2").value);
     b4 = document.createTextNode("=");
     z5.innerHTML = parseFloat(document.getElementById("nummer1").value)/parseFloat(document.getElementById("nummer2").value);


     element.appendChild(z1);
     element.appendChild(b2);
     element.appendChild(z3);
     element.appendChild(b4);
     element.appendChild(z5);
}


function darstellung() {
    let element = document.getElementById("darstellungsort");
    let n1 = document.createElement("p");
    let n2 = document.createElement("p");
    let n3 = document.createElement("p");
    n1.innerHTML = parseFloat(document.getElementById("nummer1").value);
    n2.innerHTML = parseFloat(document.getElementById("nummer2").value);
    n3.innerHTML = parseFloat(document.getElementById("nummer1").value)+parseFloat(document.getElementById("nummer2").value);
    element.appendChild(n1);
    element.appendChild(n2);
    element.appendChild(n3);
}
