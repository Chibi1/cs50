// console.log("Hello World");

var calcString = [];
var base;
var power = ["(", "1", ")"]
var answer = "0";
answered = true;
operating = false;
inBracket = false;
powered = false;

$(document).ready(function(){
    $("#screen").val(answer);
    // append values from button press to array
    $("input").click(function() {
        var value = $(this).val();
        // numerical checks for appending value to array
        if ($.isNumeric(value)) {
            // check whether new calc should start or can append num to previous calculation
            if (answered == true) {
                answered = false;
                operating = false;
                calcString = [];
                calcString.push(value);
                $("#screen").val(calcString.join(""));
            }
            else if (powered == true) {
                power.push(value);
                calcString.push(value);
                $("#screen").val(calcString.join(""));
                console.log(power.join(""));
            }
            else {
                operating = false;
                calcString.push(value);
                $("#screen").val(calcString.join(""));
            }
            
        }
        // operator "checks" for appending value to array
        if (["+", "-", "*", "/", "."].includes(value)) {
            if (operating == false) {
                answered = false;
                operating = true;
                calcString.push(value);
                $("#screen").val(calcString.join(""));
                // console.log(calcString[-1]);
            }
        }
        // implement parenthesis
        if (value == "(") {
            answered = false;
            operating = true;
            inBracket = true;
            calcString.push(value);
            $("#screen").val(calcString.join(""));
        }
        else if (value == ")") {
            operating = false;
            inBracket = false;
            calcString.push(value);
            $("#screen").val(calcString.join(""));
        }
        // implement power
        if (value == "x^y" && operating == false) {
            answered = false;
            // operating = true;
            inBracket = true;
            powered = true;
            base = calcString.join("")
            calcString.unshift("(");
            calcString.push(")^(");
            power = [];
            power.unshift("(");
            $("#screen").val(base);
            console.log(base);            
        }
        else if (value == ")" && powered == true) {
            operating = false;
            inBracket = false;
            powered = false;
            power.push(value)
        }
        // implement delete button
        if (value == "DEL") {
            answer = 0;
            answered = true;
            operating = false;
            inBracket = false;
            $("#screen").val(answer);
            console.log(answer);
            calcString = [];
        }
        
        // update calculator screen
        if (value != "=") {
            
            console.log(calcString.join(""));
        }
        else {
            if (calcString.length != 0) {
                if (!powered) {
                    answer = eval(calcString.join(""));
                    $("#screen").val(answer);
                    answered = true;
                    operating = false;
                    inBracket = false;
                    console.log(answer);
                }
                else if (powered && calcstring[calcString.length - 2] == ")") {
                    answer = Math.pow(eval(base), eval(power));
                    $("#screen").val(answer);
                    answered = true;
                    operating = false;
                    inBracket = false;
                    console.log(base);
                    console.log(power);
                    console.log(answer);
                }
                
            }
            else {
                $("#screen").val(answer);
                answered = true;
                operating = false;
                inBracket = false;     
                console.log(answer);
            }
            
        }

        console.log("answered: " + answered);
        console.log("operating: " + operating);
        console.log("inBracket: " + inBracket);
        console.log("powered: " + powered);
        
    })
    

    // cancel out post button click focus
    $(".btn-primary").mouseup(function(){
        $(this).blur();
    })
})
