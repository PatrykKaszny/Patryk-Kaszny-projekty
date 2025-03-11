package pl.pols.lab.services;

import Model.Product;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import pl.polsl.lab.model.SingletonModel;

/**
 * Servlet to handle retrieving and displaying the list of products in JSON format.
 * It fetches the list of products from the Singleton model and returns it to the
 * client in a structured JSON response.
 * 
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
@WebServlet("/productList")
public class ProductListServlet extends HttpServlet {

    /**
     * Handles the GET request. Retrieves the list of products from the Singleton
     * model and returns it in JSON format.
     * 
     * @param request the HTTP request object
     * @param response the HTTP response object
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set the content type of the response to JSON
        response.setContentType("application/json;charset=UTF-8");
        PrintWriter out = response.getWriter();

        // Retrieve the list of products from the Singleton model
        List<Product> products = SingletonModel.getInstance().getAllProductList();

        // Start JSON array
        out.print("[");

        // Iterate through the list of products and build the JSON response
        for (int i = 0; i < products.size(); i++) {
            Product product = products.get(i);

            // Add each product as a JSON object with 'id' and 'name' fields
            out.print("{\"id\": " + i + ", \"name\": \"" + product.getName() + "\"}");

            // If this is not the last product, add a comma
            if (i < products.size() - 1) {
                out.print(",");
            }
        }

        // End the JSON array
        out.print("]");
    }
}
