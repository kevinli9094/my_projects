<!DOCTYPE html>
<html>
<head>
	<style>
		body {
			background-color: #f1f1d1;
		}
		#para1 {font-size:30px; color:blue;}
		table, th, td {
			width:600px;
			border: 1px solid black;
			border-collapse: collapse;
			background-color: #f1f1c1;
		}
		th, td {
			text-align: left;
		}
	</style>
	<title>facility calendar</title>
</head>
<body>
<?php
$servername = "127.0.0.1";
$username = "root@localhost";
$password = "";
function is_there_ball_on($this_date, $conn) {
	$sql = "SELECT * FROM `facility calendar` where date='$this_date'";
	$result = mysqli_query($conn, $sql);

	if (mysqli_num_rows($result) > 0){
		echo "<table>";
		echo "<tr>";
		echo "<td>type</td>";
		echo "<td>time</td>";
		echo "<td>location</td>";
		echo "</tr>";
		while($row =  mysqli_fetch_assoc($result)) {
			echo "<tr>";
			if ($row["type"] == 1){
				$rowtype = "open basketball";
			}
			else {
				$rowtype = "multisports";
			}
			echo "<td>$rowtype</td>";
			echo "<td>$row[start_time] - $row[end_time]</td>";
			echo "<td>$row[location]</td>";
			echo "</tr>";
		}
		echo "</table>";
	} else {
		echo "No ball for today and go study!";
	}
}
$conn = new mysqli($servername, $username, $password, "test");

if ($conn->connect_error) {
	die("connection fail" . $conn->connect_error);
}

//$d=strtotime("today");
//$d1=date("Y-m-d", $d);

//$d=strtotime("tomorrow");
//$d2=date("Y-m-d", $d);

//$d=strtotime("+2 days");
//$d3=date("Y-m-d", $d);

//$d=strtotime("+3 days");
//$d4=date("Y-m-d", $d);
//$d=strtotime("+4 days");
//$d5=date("Y-m-d", $d);
//$d=strtotime("+5 days");
//$d6=date("Y-m-d", $d);
//$d=strtotime("+6 days");
//$d7=date("Y-m-d", $d);
$d1=date("Y-m-d", mktime(0,0,0,12,1,2014));
$d2=date("Y-m-d", mktime(0,0,0,12,2,2014));
$d3=date("Y-m-d", mktime(0,0,0,12,3,2014));
$d4=date("Y-m-d", mktime(0,0,0,12,4,2014));
$d5=date("Y-m-d", mktime(0,0,0,12,5,2014));
$d6=date("Y-m-d", mktime(0,0,0,12,6,2014));
$d7=date("Y-m-d", mktime(0,0,0,12,7,2014));
$theDate = "";
if ($_SERVER["REQUEST_METHOD"] == "POST") {
	if (empty($_POST["date"])) {
		$dateErr = "Please input a date";
	}
	else{
		$theDate = test_input($_POST["date"]);
	}
}
function test_input($data) {
	$data = trim($data);
	$data = stripslashes($data);
	$data = htmlspecialchars($data);
	return $data;
}
?>
<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
<p>Enter a date to see the schedule on that day. (YYYY-mm-dd)</p>
Date: <input type="text" name = "date" value="<?php echo $theDate?>">
<br><br>
   <input type="submit" name="submit" value="Submit"> 
</form>
<br></br>

<p id="para1"><?php echo date("Y-m-d",strtotime($theDate)); ?></p>
<?php
if (empty($theDate)) {
} else {
is_there_ball_on(date("Y-m-d",strtotime($theDate)), $conn);
}
?>
<p id="para1">today</p>
<?php
is_there_ball_on($d1, $conn);
?>

<p id="para1">tomorrow</p>
<?php
is_there_ball_on($d2, $conn);
?>

<p id="para1"><?php echo "$d3" ?></p>
<?php
is_there_ball_on($d3, $conn);
?>

<p id="para1"><?php echo "$d4" ?></p>
<?php
is_there_ball_on($d4, $conn);
?>

<p id="para1"><?php echo "$d5" ?></p>
<?php
is_there_ball_on($d5, $conn);
?>

<p id="para1"><?php echo "$d6" ?></p>
<?php
is_there_ball_on($d6, $conn);
?>

<p id="para1"><?php echo "$d7" ?></p>
<?php
is_there_ball_on($d7, $conn);
?>
</body>
</html>
