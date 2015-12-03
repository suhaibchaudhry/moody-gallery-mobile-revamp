<?php
$i = db_query("select * from content_field_artist_work");
while ($img = db_fetch_object($i)) {
	$data = unserialize($img->field_artist_work_data);
	//var_dump($data);
	$data["alt"] = preg_replace('/<\W*br\W*\/?\W*>/', '  ', $data["alt"]);
	$data["title"] = preg_replace('/<\W*br\W*\/?\W*>/', '  ', $data["title"]);
	$data = serialize($data);
	db_query("UPDATE content_field_artist_work SET field_artist_work_data = '%s' WHERE vid = '%d' AND nid = '%d' AND delta = '%d' AND field_artist_work_fid = '%d' AND field_artist_work_list = '%d'", $data, $img->vid, $img->nid, $img->delta, $img->field_artist_work_fid, $img->field_artist_work_list);
}
