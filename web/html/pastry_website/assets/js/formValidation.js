$(".modal-form-check").click(function(){
	formCheck();
});
$("#individual-order").submit(function(event){
	if (formCheck()) {
		let nameArray = ["individual-type", "what-first", "what-second", "address", "date", "daytime", "pay-method", "name", "email", "phone"];
		let $form = $("#individual-order");
		let data = "";
		for (let i = 0; i < nameArray.length; ++i){
			data += nameArray[i] + " = " + $form.find("[name="+nameArray[i]+"]").val() + "\n";
		}
		// var posting = $.post( url, { s: term } );
		alert(data);
	}
	else { event.preventDefault(); }
});

function formCheck(){
	let flagArray = [];
	let classArray = [".what-first", ".what-second", ".address", ".date", ".name", ".email", ".phone"];
	flagArray.push($(classArray[0]).val().length>3);
	flagArray.push($(classArray[1]).val().length>20);
	flagArray.push($(classArray[2]).val()!="");
	flagArray.push((/\d+\.\d+\.\d+/.test($(classArray[3]).val()))?(true):((/\d+\/\d+\/\d+/.test($(classArray[3]).val()))?(true):((/\d+-\d+-\d+/.test($(classArray[3]).val()))?(true):(false))));
	flagArray.push(/[a-zA-Zа-яА-Я]+\s[a-zA-Zа-яА-Я]+\s[a-zA-Zа-яА-Я]+/.test($(classArray[4]).val()));
	flagArray.push(/.+@[0-9a-zA-Z\-]+\.[a-z]+/.test($(classArray[5]).val()));
	flagArray.push((/[0-9]+/.test($(classArray[6]).val()))?(true):((/\+[0-9]+/.test($(classArray[6]).val()))?(true):(false)));
	/* data-toggle="popover" data-trigger="focus" data-placement="bottom" data-content="" */
	let check = true;
	for (let i = 0; i < flagArray.length; ++i) {
		if (flagArray[i]) {
			$(classArray[i]).removeClass("alert-danger");
			$(classArray[i]).addClass("alert-success");
			$(classArray[i]).popover("disable");
		} else {
			check = false;
			$(classArray[i]).removeClass("alert-success");
			$(classArray[i]).addClass("alert-danger");
			$(classArray[i]).popover("enable");
		}
	}
	return check;
}