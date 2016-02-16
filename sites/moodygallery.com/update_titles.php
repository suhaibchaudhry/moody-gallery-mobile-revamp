<?php
$matches = array();
$i = db_query("select * from content_field_artist_work");
while ($img = db_fetch_object($i)) {
	$data = unserialize($img->field_artist_work_data);

	preg_match_all('/[^\S\n]{2}/', $data["alt"], $matches, PREG_OFFSET_CAPTURE);
	$done = 0;
	foreach($matches[0] as $key => $match) {
		if($key != 1) {
			$data["alt"] = substr_replace($data["alt"], "<br />", $match[1]+($done*4), strlen($match[0]));
			$done++;
		}
	}
	preg_match_all('/[^\S\n]{2}/', $data["title"], $matches, PREG_OFFSET_CAPTURE);
	$done = 0;
        foreach($matches[0] as $key => $match) {
                if($key != 1) {
                        $data["title"] = substr_replace($data["title"], "<br />", $match[1]+($done*4), strlen($match[0]));
			$done++;
                }
        }
	//$data["alt"] = preg_replace('/[^/S/n]{2}/', '  ', $data["alt"]);
	//$data["title"] = preg_replace('/<\W*br\W*\/?\W*>/', '  ', $data["title"]);
	$data = serialize($data);
	var_dump($data);
	
	db_query("UPDATE content_field_artist_work SET field_artist_work_data = '%s' WHERE vid = '%d' AND nid = '%d' AND delta = '%d' AND field_artist_work_fid = '%d' AND field_artist_work_list = '%d'", $data, $img->vid, $img->nid, $img->delta, $img->field_artist_work_fid, $img->field_artist_work_list);
}
