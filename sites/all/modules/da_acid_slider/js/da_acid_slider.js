$(document).ready(function() {
	var Slider = {};
	Slider.currentSlide = 0;
	Slider.childWidth = $(".da_slider").width();
	Slider.secondaryPosition = $(".da_element > div").position();
	Slider.parentWidth = 0;
	Slider.elementCount = 0;
	Slider.intervalID = 0;
	
	da_acid_slider_init("da_element", "da_slider", Slider);
	da_acid_slider_begin("da_element", "da_slider", Drupal.settings.da_acid_slider.primary_animation, Drupal.settings.da_acid_slider.secondary_animation, parseInt(Drupal.settings.da_acid_slider.primary_speed), parseInt(Drupal.settings.da_acid_slider.secondary_speed), parseInt(Drupal.settings.da_acid_slider.slider_delay), Slider);
	
	$(".da_slider").hover(function() {
		da_acid_slider_pause(Slider);
	}, function() {
		da_acid_slider_begin("da_element", "da_slider", Drupal.settings.da_acid_slider.primary_animation, Drupal.settings.da_acid_slider.secondary_animation, parseInt(Drupal.settings.da_acid_slider.primary_speed), parseInt(Drupal.settings.da_acid_slider.secondary_speed), parseInt(Drupal.settings.da_acid_slider.slider_delay), Slider);
	});	
});

function da_acid_slider_begin(elementClass, sliderClass, primaryEasing, secondaryEasing, primarySpeed, secondarySpeed, delayTime, Slider) {
	Slider.intervalID = setInterval(function() {
		da_acid_slider_nextSlide(elementClass, sliderClass, primaryEasing, secondaryEasing, primarySpeed, secondarySpeed, Slider);
	}, (delayTime+primarySpeed+secondarySpeed));
}

function da_acid_slider_pause(Slider) {
	clearInterval(Slider.intervalID);
}

function da_acid_slider_init(elementClass, sliderClass, Slider) {
	$("."+elementClass).each(function(index, e) {
		Slider.parentWidth += $(this).width();
		Slider.elementCount++;
	});

	$("."+sliderClass).css("width", Slider.parentWidth);
}

function da_acid_slider_nextSlide(elementClass, sliderClass, primaryEasing, secondaryEasing, primarySpeed, secondarySpeed, Slider) {
	$("."+elementClass+" > div").css("left", Slider.secondaryPosition.left);
	if(Slider.currentSlide == Slider.elementCount-1) {
		var leftPosition = 0;
	} else {
		var leftPosition = -(Slider.childWidth*(Slider.currentSlide+1));
	}
	$("."+elementClass+" > div").eq(Slider.currentSlide).animate({left: -(Slider.childWidth+Slider.secondaryPosition.left)}, secondarySpeed, secondaryEasing, function() {
			$("."+sliderClass).animate({left: leftPosition}, primarySpeed, primaryEasing, function() {
				if(Slider.currentSlide == Slider.elementCount-1) {
					Slider.currentSlide = 0;
				} else {
					Slider.currentSlide++;
				}
			});
	});
}