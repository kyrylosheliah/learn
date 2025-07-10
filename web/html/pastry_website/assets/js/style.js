$(window).scroll(function() {
	if($(this).scrollTop() == 0) {
		$('#scrollBegin').fadeOut();
	} else if ($(window).height() + $(this).scrollTop() == $(document).height()) {
		$('#scrollBegin').fadeIn();
		$('#scrollBegin').css("bottom", "128px");
	} else {
		$('#scrollBegin').css("bottom", "16px");
		$('#scrollBegin').fadeIn();
	}
});
$('#scrollBegin').click(function() { $('html,body').animate({scrollTop:0},200); });

$(".mobilebar-menu-toggle").on('click', function(){
	$(".mobilebar-menu").toggleClass("mmt_active");
	$(".mobilebar-navigation").toggleClass("mn_active");
});

$(".quantity-minus").on('click', function(){
	var count = parseInt($(".quantity-number").val());
	if(count <= 1){
		$(".quantity-minus").addClass("disabled");
	}else{
		$(".quantity-minus").removeClass("disabled");
		$(".quantity-number").val(count-1);
		if(count - 1 <= 1){
			$(".quantity-minus").addClass("disabled");
		}
	}
});
$(".quantity-plus").on('click', function(){
	var count = parseInt($(".quantity-number").val());
	if(count >= 100){
		$(".quantity-minus").addClass("disabled");
	}else{
		$(".quantity-minus").removeClass("disabled");
		$(".quantity-number").val(count+1);
		if(count + 1 >= 100){
			$(".quantity-minus").addClass("disabled");
		}
	}
});

$(".tab-recipe").css("display", "none");
$(".switch-recipe").addClass("disabled");
$(".switch-details").on('click', function(){
	switchTab(".switch-details", ".tab-details");
});
$(".switch-recipe").on('click', function(){
	switchTab(".switch-recipe", ".tab-recipe");
});
function switchTab(target, tabId) {
	$(".tab-content-item").css("display", "none");
	$(".tab-switches-button").addClass("disabled");
	$(tabId).css("display", "flex");
	$(target).removeClass("disabled");
}

$(".accordion-header-button").on("click", function(){
	$(this).parent().parent().toggleClass("active");
});