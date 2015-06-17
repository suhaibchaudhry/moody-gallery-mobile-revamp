<?php
/*
Arguments:
	$unit: The simpleXML Object representing a unit available for reservation.
	$preset: The ImageCache present used to resize the property image thumbnails.
	$row_classes : System generated row classes to select even,odd, first or last entities distinctively form css.
*/
?>
<div class="unit-row <?php print $row_classes ?>">
	<div class="property-image-cache">
    	<?php if(!empty($unit->PictureLink)) { ?>
    	<img src="<?php print imagecache_external_generate_path('http://www.aaxsys.com/'.$unit->PictureLink, $preset) ?>" alt="<?php print $unit->Name ?>" />
        <?php } else { ?>
        <img src="<?php print drupal_get_path('module', 'aaxsys_api') ?>/images/imagemissing.png" alt="Image not available" width="165" height="125" />
        <?php } ?>
     </div>
    <div class="property-details">
    	<h2><?php print $unit->Name ?></h2>
        <p class="property-location">
       	<span class="city"><?php print $unit->City ?></span>
        <span class="state"><?php print $unit->State ?><?php if(!empty($unit->Country)) { print ', '.$unit->Country; } ?></span>
        </p>
        <?php if(!empty($unit->Remark)) : ?>
        <p class="property-desc"><?php print $unit->Remark ?></p>
        <?php endif; ?>
        <?php if(!empty($unit->Neighborhood) || !empty($unit->CrossStreets) || !empty($unit->Bedrooms) || !empty($unit->Bathrooms)) : ?>
        <div class="property-quick-info"><?php print aaxsys_api_field_table(array('Neighborhood' => $unit->Neighborhood, 'Cross streets' => $unit->CrossStreets, 'Bedrooms' => $unit->Bedrooms, 'Bathrooms' => $unit->Bathrooms), 2); ?></div>
        <?php endif; ?>
    </div>
    <div class="property-actions">
    <?php if(!empty($unit->MRate)) : ?>
		<p class="property-monthly-rate"><strong>Monthly: </strong>$<?php print money_format('%i', (float)$unit->MRate) ?></p>
    <?php endif; ?>
    <a href="#" class="property-info-link" rel="<?php print $unit->InformationLink ?>" title="<?php print $unit->Name ?>">More Information</a>
    </div>
</div>