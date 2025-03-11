package pl.pols.lab.services;

import Model.Product;
import jakarta.servlet.ServletContext;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import pl.polsl.lab.model.DataSource;
import pl.polsl.lab.model.SingletonModel;

/**
 * Servlet to handle the editing of product details. It allows displaying an
 * editable form for a product and processing the changes submitted by the user.
 * 
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
@WebServlet("/editProduct")
public class EditProductServlet extends HttpServlet {

    /**
     * Handles the GET request. Retrieves the product based on its ID and displays
     * an editable form to the user for modifying product details (name, protein,
     * carbs, and fat).
     * 
     * @param request the HTTP request object containing the request data
     * @param response the HTTP response object to send the response data
     * @throws ServletException if a servlet-specific error occurs while processing the request
     * @throws IOException if an I/O error occurs while generating the response
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        System.out.println("Received request to edit product");

        int productId;
        try {
            // Try to parse the product ID from the request parameter
            productId = Integer.parseInt(request.getParameter("id"));
        } catch (NumberFormatException e) {
            // Handle invalid product ID
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid product ID");
            return;
        }

        // Retrieve the product from the Singleton model
        Product product = SingletonModel.getInstance().getAllProductList().get(productId);
        if (product == null) {
            // Handle case where product is not found
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Product not found");
            return;
        }

        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();

        // Output the HTML form for editing the product details
        out.println("<div id='editProductForm' data-product-id='" + productId + "'>");
        out.println("<table>");
        out.println("<tr>");
        out.println("<td><input type='text' id='editName' value='" + product.getName() + "' /></td>");
        out.println("<td><input type='number' id='editProtein' value='" + product.getProtein() + "' min='1' required /></td>");
        out.println("<td><input type='number' id='editCarb' value='" + product.getCarb() + "' min='1' required /></td>");
        out.println("<td><input type='number' id='editFat' value='" + product.getFat() + "' min='1' required /></td>");
        out.println("</tr>");
        out.println("</table>");

        out.println("<div style='margin-top: 10px; text-align: center;'>");
        out.println("<button onclick='submitEditForm(" + productId + ")'>Save</button>");
        out.println("</div>");
    }

    /**
     * Handles the POST request. It processes the form submission, validates the
     * product details, and updates the product in the Singleton model.
     * 
     * @param request the HTTP request object containing the submitted form data
     * @param response the HTTP response object to send the status of the update
     * @throws ServletException if a servlet-specific error occurs during request processing
     * @throws IOException if an I/O error occurs while generating the response
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        int productId;
        ServletContext context = request.getServletContext();
        DataSource dataSource = (DataSource) context.getAttribute("DataSource");
        
        try {
            // Read updated data from the form
            productId = Integer.parseInt(request.getParameter("id"));
            String name = request.getParameter("name");
            int protein = Integer.parseInt(request.getParameter("protein"));
            int carb = Integer.parseInt(request.getParameter("carb"));
            int fat = Integer.parseInt(request.getParameter("fat"));

            System.out.println("ID: " + productId);
            System.out.println("Name: " + name);
            System.out.println("Protein: " + protein);
            System.out.println("Carb: " + carb);
            System.out.println("Fat: " + fat);

            // Validation to ensure that protein, carbs, and fat are positive values
            if (protein <= 0 || carb <= 0 || fat <= 0) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Values must be positive");
                return;
            }

            // Update the product in the Singleton model
            Product p = new Product(name, protein, carb, fat, 100);
            SingletonModel.getInstance().getAllProductList().set(productId, p);
            dataSource.update(p);

            // Send a success response
            response.setStatus(HttpServletResponse.SC_OK);
        } catch (Exception e) {
            // Handle any exceptions (e.g., invalid data)
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid data");
        }
    }
}
