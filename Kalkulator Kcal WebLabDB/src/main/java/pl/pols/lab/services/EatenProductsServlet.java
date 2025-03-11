package pl.pols.lab.services;

import Model.EatenProduct;
import Model.Product;
import jakarta.servlet.ServletContext;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import pl.polsl.lab.model.DataSource;
import pl.polsl.lab.model.SingletonModel;

/**
 * Servlet for handling the data of consumed products. It processes requests to
 * display, delete, and edit consumed products, and calculates the totals for
 * calories and macronutrients.
 * 
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
@WebServlet("/consumedProductsData")
public class EatenProductsServlet extends HttpServlet {

    /**
     * Initializes the servlet. This method loads the consumed product data from
     * the DataSource and adds it to the SingletonModel for easy access.
     */
    @Override
    public void init() {
        var context = getServletContext();        
        DataSource dataSource = (DataSource) context.getAttribute("DataSource");  
        for (EatenProduct p : dataSource.getEatenProductList()) {     
            SingletonModel.getInstance().addEatenProducts(
                p.product.getName(), p.product.getGrams(), p.product.getCalories(),
                p.product.getProtein(), p.product.getCarb(), p.product.getFat());
        }    
    }

    /**
     * Handles the HTTP GET request. It retrieves and displays the list of consumed
     * products, along with the total calories and macronutrients (protein, carbs, and fats).
     * It also sends the data as an HTML table to be rendered on the client.
     * 
     * @param request the HTTP request object
     * @param response the HTTP response object to send the product data
     * @throws ServletException if a servlet-specific error occurs during the request processing
     * @throws IOException if an I/O error occurs while generating the response
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        // Get the list of consumed products from the singleton model
        List<Product> consumedProducts = SingletonModel.getInstance().getEatenProductList();
        double totalKcal = 0;
        double totalProtein = 0;
        double totalFat = 0;
        double totalCarb = 0;

        // Calculate the total calories and macronutrients
        for (Product product : consumedProducts) {
            totalKcal += product.getKcal();
            totalProtein += product.getProtein();
            totalFat += product.getFat();
            totalCarb += product.getCarb();
        }

        // Send the response to the client
        try (PrintWriter out = response.getWriter()) {
            if (consumedProducts.isEmpty()) {
                out.println("<tr><td colspan='7'>No consumed products</td></tr>");
            } else {
                for (Product product : consumedProducts) {
                    out.println("<tr>");
                    out.println("<td>" + product.getName() + "</td>");
                    out.println("<td>" + product.getWeight() + " g</td>");
                    out.println("<td>" + product.getProtein() + "</td>");
                    out.println("<td>" + product.getCarb() + "</td>");
                    out.println("<td>" + product.getFat() + "</td>");
                    out.println("<td>" + product.getKcal() + "</td>");
                    out.println("<td>");
                    out.println("<button class='delete-btn' data-name='" + product.getName() + "'>Delete</button>");
                    out.println("<button class='edit-btn' data-name='" + product.getName() + "'>Edit</button>");
                    out.println("</td>");
                    out.println("</tr>");
                }
            }

            // Add totals section at the end of the table
            out.println("<tr class='totals'>");
            out.println("<td colspan='2'>Total</td>");
            out.println("<td>" + totalProtein + "</td>");
            out.println("<td>" + totalCarb + "</td>");
            out.println("<td>" + totalFat + "</td>");
            out.println("<td>" + totalKcal + "</td>");
            out.println("<td></td>");
            out.println("</tr>");
        }
    }

    /**
     * Handles the HTTP POST request. It processes actions for deleting or editing a
     * consumed product. If editing, it updates the product's weight and recalculates
     * the associated nutritional values.
     * 
     * @param request the HTTP request object containing the action (delete or edit) and necessary parameters
     * @param response the HTTP response object to send back the result of the action
     * @throws ServletException if a servlet-specific error occurs during the request processing
     * @throws IOException if an I/O error occurs while generating the response
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String action = request.getParameter("action");
        ServletContext context = request.getServletContext();
        DataSource dataSource = (DataSource) context.getAttribute("DataSource");

        // Handle delete action
        if ("delete".equals(action)) {
            String productName = request.getParameter("name");

            // Remove the eaten product from the model
            dataSource.deleteEatenProduct(productName);
            SingletonModel.getInstance().removeEatenProductList(productName);

            // Respond to the client
            response.setContentType("text/plain");
            response.getWriter().write("Product deleted");
        } 
        // Handle edit action
        else if ("edit".equals(action)) {
            String productName = request.getParameter("name");
            String newWeightStr = request.getParameter("weight");

            try {
                // Parse the new weight value
                double newWeight = Double.parseDouble(newWeightStr);

                // Update the product's weight in the model
                dataSource.updateEatenProduct(productName, (int) newWeight);
                Product updatedProduct = SingletonModel.getInstance().updateProductWeight(productName, (int) newWeight);

                if (updatedProduct != null) {
                    // Prepare a JSON response with updated product details
                    response.setContentType("application/json");
                    response.setCharacterEncoding("UTF-8");

                    String jsonResponse = String.format(
                        "{ \"message\": \"Product weight updated\", \"weight\": %d, \"protein\": %.2f, \"carb\": %.2f, \"fat\": %.2f, \"kcal\": %.2f }",
                        updatedProduct.getWeight(),
                        updatedProduct.getProtein(),
                        updatedProduct.getCarb(),
                        updatedProduct.getFat(),
                        updatedProduct.getKcal()
                    );

                    response.getWriter().write(jsonResponse);
                } else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    response.getWriter().write("Product not found");
                }
            } catch (NumberFormatException e) {
                // Handle invalid weight format
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Invalid weight format");
            }
        }
    }
}
