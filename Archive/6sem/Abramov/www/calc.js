last=0;
result=0;
operation="";
lastMove=true;
function rid() {
	form.output.value="0";
	last = 0;
	result = 0;
	operation = "";
	lastMove = true;
}

function negate() {
	if (lastMove == true){
		form.output.value = 0;
	}
	form.output.value = form.output.value*-1;
}

function total(num) {
	val = Math.PI;
	if (num == val || lastMove == true){
	 form.output.value=num;
	  if (num!=val) {
			lastMove = false;
		}
	}else{	
	  result = form.output.value;
	   num = result+num;
		form.output.value = num;
	}
}

function compute(sign) {
 switch (operation) {
		
		case "add":	form.output.value = last*1+form.output.value*1;
				break;
		case "subtract":	form.output.value = last-form.output.value;
				break;
		case "multiply":	form.output.value = last*form.output.value;
				break;
		case "divide":	form.output.value = last/form.output.value;
				break;
	}
 last = form.output.value*1;
  operation = sign;
   lastMove = true;		
}