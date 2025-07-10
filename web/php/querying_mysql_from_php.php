<!doctype html>
<html lang="en">
   <head>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>A Basic HTML5 Template</title>
      <meta name="description" content="A simple HTML5 Template for new projects.">
      <meta name="author" content="SitePoint">
      <meta property="og:title" content="A Basic HTML5 Template">
      <meta property="og:type" content="website">
      <meta property="og:url" content="https://www.sitepoint.com/a-basic-html5-template/">
      <meta property="og:description" content="A simple HTML5 Template for new projects.">
      <meta property="og:image" content="image.png">
      <link rel="icon" href="/favicon.ico">
      <link rel="icon" href="/favicon.svg" type="image/svg+xml">
      <link rel="apple-touch-icon" href="/apple-touch-icon.png">
      <link rel="stylesheet" href="css/styles.css?v=1.0">
   </head>
   <body>
      <!-- your content here... -->
      <?
         ?>
      <form name="form" action="" method="post">
         <table border=1 cellpadding=5 style='border-collapse: collapse'>
            <tr>
               <td>db name</td>
               <td><input type="text" name="SQLDBname" value="<?
                  printf((empty($_POST["SQLDBname"]))?("mydb"):($_POST["SQLDBname"]));
                  ?>"></td>
            </tr>
            <tr>
               <td>general request</td>
               <td><textarea cols="40" rows="5" name="SQLrequest"><?
                  printf((empty($_POST["SQLrequest"]))?("select * from employees"):($_POST
                  ["SQLrequest"]));
                  ?></textarea></td>
            </tr>
            <tr>
               <td>browse request (called after insert, update, delete)</td>
               <td><textarea cols="40" rows="1" name="SQLdefault"><?
                  printf((empty($_POST["SQLdefault"]))?("select * from employees"):($_POST
                  ["SQLdefault"]));
                  ?></textarea></td>
            </tr>
            <tr>
               <td>&nbsp;</td>
               <td><input type="submit" value="Request"></td>
            </tr>
         </table>
      </form>
      <br>
      <?
         function senddbrequest(&$mysqldbname, &$mysqlrequest)
         {
         if(empty($mysqldbname) or empty($mysqlrequest))
         {
         $result["mysqlrequest"] = "noinput";
         return $result;
         }
         mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
         $mysqli = new mysqli("localhost", "root", "root", $mysqldbname);
         if ($mysqli->connect_errno)
         {
         $result["mysqlrequest"] = "noconnection";
         return $result;
         }
         $query = $mysqli->query($mysqlrequest);
         $result = array();
         if (gettype($query) == "boolean")
         {
         $result["response"] = $query;
         }
         else
         {
         $result["response"] = $query->fetch_all(MYSQLI_ASSOC);
         }
         $result["mysqlrequest"] = strtolower(strtok($mysqlrequest, " "));
         return $result;
         }
         function printdbresponse(&$result)
         {
         if(!empty($result))
         {
         $metanames = array_keys($result["response"][0]);
         printf("<div><font color='green'>db responded:</font></div>");
         printf("<table border=1 cellpadding=5 style='border-collapse: collapse'>\n");
         printf("<tr>");
         foreach ($metanames as $metafield) {
         printf("<td><b>%s</b></td>\n", $metafield);
         }
         printf("<td><b>#</b></td>\n");
         $counter = 0;
         printf("</tr>\n");
         foreach ($result["response"] as $row) {
         printf("<tr>");
         foreach ($row as $field) {
         printf("<td>%s</td>\n", $field);
         }
         printf("<td><b>%s</b></td>\n", ++$counter);
         printf("</tr>\n");
         }
         printf("</table>\n");
         }
         else
         {
         printf("<div><font color='gray'>db response empty.</font></div>");
         }
         }
         function sqldbjob()
         {
         $result = senddbrequest($_POST["SQLDBname"], $_POST["SQLrequest"]);
         switch($result["mysqlrequest"])
         {
         case "select":
         printdbresponse($result);
         break;
         case "insert":
         case "update":
         case "delete":
         if($result["response"])
         {
         echo "<div><font color='green'>db modification request succeded</
         font></div>";
         }
         else
         {
         echo "<div><font color='red'>db modification request failed</font></
         div>";
         }
         if(empty($_POST["SQLdefault"]))
         {
         break;
         }
         $tmpreq = $_POST["SQLdefault"];
         $result = senddbrequest($_POST["SQLDBname"], $tmpreq);
         printdbresponse($result);
         break;
         case "noinput":
         echo "<div><font color='gray'>db name or request empty</font></div>";
         break;
         case "noconnection":
         echo "<div><font color='red'>db connection error </font></div>";
         break;
         default:
         echo "<div><font color='red'>you shouldnt see this</font></div>";
         break;
         }
         }
         sqldbjob();
         ?>
      <script src="js/scripts.js"></script>
   </body>
</html>
